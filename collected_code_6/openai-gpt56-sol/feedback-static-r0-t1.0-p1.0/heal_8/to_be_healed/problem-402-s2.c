#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus, int *error)
{
    uint64_t *row;
    uint64_t result;
    size_t count;

    *error = 0;

    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(*row) - 1U)) {
        *error = ENOMEM;
        return 0;
    }

    count = (size_t)r + 1U;
    row = calloc(count, sizeof(*row));
    if (row == NULL) {
        *error = ENOMEM;
        return 0;
    }

    row[0] = 1U % modulus;

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t limit = i < r ? i : r;

        for (uint64_t j = limit; j > 0; --j) {
            row[j] = add_mod(row[j], row[j - 1U], modulus);
        }
    }

    result = row[r];
    free(row);
    return result;
}

static int is_space_char(unsigned char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int parse_uint64_token(const char *token, uint64_t *value)
{
    uint64_t result = 0;

    if (*token == '\0') {
        return 0;
    }

    while (*token != '\0') {
        unsigned int digit;

        if (*token < '0' || *token > '9') {
            return 0;
        }

        digit = (unsigned int)(*token - '0');

        if (result > (UINT64_MAX - digit) / 10U) {
            return 0;
        }

        result = result * 10U + digit;
        ++token;
    }

    *value = result;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];
    char *cursor;
    uint64_t values[3];
    uint64_t result;
    int error;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (line[0] != '\0') {
        size_t length = 0;

        while (line[length] != '\0') {
            ++length;
        }

        if (length > 0 && line[length - 1] != '\n' && !feof(stdin)) {
            int ch;

            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    cursor = line;

    for (size_t i = 0; i < 3; ++i) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char token[32];
        size_t length = 0;

        while (*cursor != '\0' && is_space_char((unsigned char)*cursor)) {
            ++cursor;
        }

        while (*cursor != '\0' && !is_space_char((unsigned char)*cursor)) {
            if (length + 1U >= sizeof(token)) {
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }

            token[length++] = *cursor++;
        }

        token[length] = '\0';

        if (!parse_uint64_token(token, &values[i])) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    while (*cursor != '\0' && is_space_char((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char extra[256];

        if (fgets(extra, sizeof(extra), stdin) == NULL) {
            if (ferror(stdin)) {
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        for (size_t i = 0; extra[i] != '\0'; ++i) {
            if (!is_space_char((unsigned char)extra[i])) {
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
        }
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