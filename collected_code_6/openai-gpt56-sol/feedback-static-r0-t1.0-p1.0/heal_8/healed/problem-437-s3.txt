#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static void remove_odd_characters(char *string)
{
    size_t read_index = 0U;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        if ((read_index & 1U) == 0U) {
            string[write_index++] = string[read_index];
        }
        ++read_index;
    }

    string[write_index] = '\0';
}

int main(void)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *string = malloc(capacity);

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    string[0] = '\0';

    for (;;) {
        char *result;
        size_t available;

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_string;

            if (capacity > SIZE_MAX / 2U) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        available = capacity - length;
        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        result = fgets(string + length, (int)available, stdin);
        if (result == NULL) {
            if (ferror(stdin)) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        while (string[length] != '\0' && string[length] != '\n') {
            ++length;
        }

        if (string[length] == '\n') {
            break;
        }

        if (feof(stdin)) {
            break;
        }
    }

    string[length] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}