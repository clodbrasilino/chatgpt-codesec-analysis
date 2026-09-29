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
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        char *new_input = realloc(input, capacity + 1);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';

    char *start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long value = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    puts(is_sum_of_two_squares(value) ? "Yes" : "No");
    free(input);

    return EXIT_SUCCESS;
}