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
        magnitude = (uint64_t)(-(number + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % UINT64_C(4) != UINT64_C(2);
}

static bool is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static bool read_int64(int64_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    intmax_t value;
    size_t length;

    if (result == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] != '\n' && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return false;
    }

    start = buffer;
    while (is_space_character((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return false;
    }

    errno = 0;
    value = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        return false;
    }

    while (is_space_character((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        char *cursor = buffer;

        while (is_space_character((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor != '\0') {
            return false;
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