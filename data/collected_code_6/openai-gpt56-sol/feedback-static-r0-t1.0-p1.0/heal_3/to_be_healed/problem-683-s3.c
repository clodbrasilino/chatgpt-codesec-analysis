#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_two_squares(unsigned long long value)
{
    unsigned long long left = 0;
    unsigned long long right = value < ULLONG_MAX ? value + 1 : value;

    while (left < right) {
        unsigned long long middle = left + (right - left) / 2;

        if (middle != 0 && middle > value / middle) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    unsigned long long a = 0;
    unsigned long long b = left - 1;
    unsigned long long a_squared = 0;
    unsigned long long b_squared = b * b;

    while (a <= b) {
        unsigned long long remainder = value - b_squared;

        if (a_squared == remainder) {
            return true;
        }

        if (a_squared < remainder) {
            ++a;
            a_squared = a * a;
        } else {
            b_squared -= 2 * b - 1;
            --b;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] == '\0' && length == sizeof input - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
    }

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}