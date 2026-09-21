#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t p)
{
    return a >= p - b ? a - (p - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t p, int *error)
{
    uint64_t *values;
    uint64_t i;
    uint64_t j;
    uint64_t result;
    size_t count;

    *error = 0;

    if (p == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*values) - 1U)) {
        *error = ENOMEM;
        return 0;
    }

    count = (size_t)r + 1U;
    values = calloc(count, sizeof(*values));
    if (values == NULL) {
        *error = ENOMEM;
        return 0;
    }

    values[0] = 1U % p;

    for (i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (j = limit; j > 0; --j) {
            values[j] = add_mod(values[j], values[j - 1U], p);
        }

        if (i == UINT64_MAX) {
            break;
        }
    }

    result = values[r];
    free(values);
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *cursor;
    char *end;
    uint64_t values[3];
    uint64_t result;
    int error;
    size_t i;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    for (i = 0; i < 3; ++i) {
        while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
               *cursor == '\f' || *cursor == '\v') {
            ++cursor;
        }

        if (*cursor == '\0' || *cursor == '\n' || *cursor == '-') {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        values[i] = strtoumax(cursor, &end, 10);

        if (end == cursor || errno == ERANGE) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        cursor = end;
    }

    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor != '\0' && *cursor != '\n') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (values[2] == 0) {
        fputs("Modulus must be nonzero\n", stderr);
        return EXIT_FAILURE;
    }

    result = ncr_mod(values[0], values[1], values[2], &error);
    if (error != 0) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}