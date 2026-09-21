#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

static int sum_odd_naturals(uint64_t l, uint64_t r, uint64_t *result)
{
    if (result == NULL || l == 0 || l > r) {
        return 0;
    }

    uint64_t first = l | UINT64_C(1);
    uint64_t last = (r & UINT64_C(1)) != 0 ? r : r - UINT64_C(1);

    if (first > last) {
        *result = 0;
        return 1;
    }

    uint64_t count = ((last - first) / UINT64_C(2)) + UINT64_C(1);
    uint64_t factor = first + count - UINT64_C(1);

    if (factor > UINT64_MAX / count) {
        return 0;
    }

    *result = count * factor;
    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *p = *cursor;
    char *end;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-' || *p == '+') {
        return 0;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(p, &end, 10);

    if (p == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    uint64_t l;
    uint64_t r;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    const char *cursor = input;

    if (!parse_uint64(&cursor, &l) || !parse_uint64(&cursor, &r)) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid input\n", stderr);
        return 1;
    }

    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            fputs("Invalid input\n", stderr);
            return 1;
        }
    }

    if (!sum_odd_naturals(l, r, &sum)) {
        fputs("Invalid range or arithmetic overflow\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}