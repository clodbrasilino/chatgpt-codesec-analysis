#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static bool is_perfect_square(uintmax_t number)
{
    uintmax_t left = 0;
    uintmax_t right = number;

    while (left <= right) {
        uintmax_t middle = left + (right - left) / 2;

        if (middle != 0 && middle > number / middle) {
            right = middle - 1;
        } else {
            uintmax_t square = middle * middle;

            if (square == number) {
                return true;
            }

            left = middle + 1;
        }
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                errno = EOVERFLOW;
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

        size_t available = capacity - length;
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        if (fgets(buffer + length, (int)(available > INT_MAX ? INT_MAX : available),
                  stream) == NULL) {
            if (ferror(stream)) {
                free(buffer);
                return NULL;
            }

            if (length == 0) {
                buffer[0] = '\0';
            }

            return buffer;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return buffer;
        }
    }
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    char *start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    bool valid = *start != '\0' && *start != '-';
    uintmax_t number = 0;
    char *end = start;

    if (valid) {
        errno = 0;
        number = strtoumax(start, &end, 10);
        valid = errno != ERANGE && end != start;
    }

    if (valid) {
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        valid = *end == '\0';
    }

    puts(valid && is_perfect_square(number) ? "True" : "False");

    free(input);
    return EXIT_SUCCESS;
}