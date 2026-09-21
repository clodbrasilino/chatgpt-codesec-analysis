#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_two_squares(uint64_t number)
{
    uint64_t left = 0;
    /* Possible weaknesses found:
     *  Assignment 'right=0', assigned value is 0
     */
    uint64_t right = 0;

    /* Possible weaknesses found:
     *  Division by zero
     *  Division by zero. [zerodiv]
     */
    while (right <= number / right && right != 0) {
        ++right;
    }

    if (right != 0) {
        --right;
    }

    while (left <= right) {
        const uint64_t left_square = left * left;
        const uint64_t right_square = right * right;

        if (left_square == number - right_square) {
            return true;
        }

        if (left_square < number - right_square) {
            ++left;
        } else {
            --right;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares((uint64_t)value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}