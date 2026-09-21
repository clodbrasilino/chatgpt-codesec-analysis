#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(int64_t number)
{
    uint64_t magnitude;

    if (number < 0) {
        magnitude = (uint64_t)(-(number + 1)) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % UINT64_C(4) != UINT64_C(2);
}

static bool read_int64(int64_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *end;
    intmax_t value;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    if (buffer[0] == '\0') {
        return false;
    }

    char *newline = buffer;
    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline != '\n') {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return false;
    }

    *newline = '\0';

    errno = 0;
    value = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'newline' is used in the enclosing expression, the value is never actually read from 'newline' [deadcode.DeadStores]
     */
    while ((newline = fgets(buffer, sizeof buffer, stdin)) != NULL) {
        for (char *p = buffer; *p != '\0'; ++p) {
            if (*p != ' ' && *p != '\t' && *p != '\n' &&
                *p != '\r' && *p != '\f' && *p != '\v') {
                return false;
            }
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    *result = (int64_t)value;
    return true;
}

int main(void)
{
    int64_t value;

    if (!read_int64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}