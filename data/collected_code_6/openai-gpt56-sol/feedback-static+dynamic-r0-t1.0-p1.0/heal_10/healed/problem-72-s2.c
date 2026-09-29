#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_difference_of_two_squares(int64_t number)
{
    int64_t remainder = number % 4;
    return remainder != 2 && remainder != -2;
}

static int read_line(char **buffer)
{
    size_t capacity = 64;
    size_t length = 0;
    char *data;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(data);
                return 0;
            }
            break;
        }

        if (ch == '\0') {
            free(data);
            return 0;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (char)ch;
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end;
    intmax_t value;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoimax(input, &end, 10);

    if (end == input || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares((int64_t)value) ? "Yes" : "No");

    free(input);
    return EXIT_SUCCESS;
}