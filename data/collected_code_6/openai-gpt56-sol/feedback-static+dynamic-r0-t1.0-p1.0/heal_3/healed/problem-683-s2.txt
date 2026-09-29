#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_sum_of_two_squares(uint64_t number)
{
    uint64_t left = 0;
    uint64_t right = number;
    uint64_t root = 0;

    while (left <= right) {
        uint64_t middle = left + (right - left) / 2;

        if (middle != 0 && middle > number / middle) {
            right = middle - 1;
        } else {
            root = middle;
            left = middle + 1;
        }
    }

    left = 0;
    right = root;

    while (left <= right) {
        uint64_t left_square = left * left;
        uint64_t right_square = right * right;
        uint64_t remainder = number - right_square;

        if (left_square == remainder) {
            return true;
        }

        if (left_square < remainder) {
            ++left;
        } else {
            if (right == 0) {
                break;
            }
            --right;
        }
    }

    return false;
}

static bool read_value(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return false;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX) {
        free(line);
        return false;
    }

    *value = (uint64_t)parsed;
    free(line);
    return true;
}

int main(void)
{
    uint64_t value;

    if (!read_value(&value)) {
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}