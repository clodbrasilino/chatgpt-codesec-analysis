#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_two_squares(uint64_t number)
{
    uint64_t left = 0;
    uint64_t right = 0;

    while (right <= number / (right + 1)) {
        ++right;
    }

    while (left <= right) {
        uint64_t right_square = right * right;
        uint64_t remainder = number - right_square;
        uint64_t left_square = left * left;

        if (left_square == remainder) {
            return true;
        }

        if (left_square < remainder) {
            ++left;
        } else if (right > 0) {
            --right;
        } else {
            break;
        }
    }

    return false;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t value;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || value > UINT64_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares((uint64_t)value) ? "Yes" : "No");

    free(line);
    return EXIT_SUCCESS;
}