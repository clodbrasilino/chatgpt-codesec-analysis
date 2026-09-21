#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
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

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    char *start = input;

    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
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

    while (*end != '\0' && isspace((unsigned char)*end)) {
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