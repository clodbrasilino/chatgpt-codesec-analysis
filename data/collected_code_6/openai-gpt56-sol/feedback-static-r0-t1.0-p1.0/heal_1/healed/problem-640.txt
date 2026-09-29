#include <stdio.h>
#include <stdlib.h>

int remove_parenthesized(const char *input, size_t length, char **output)
{
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;
    char *result;

    if (input == NULL || output == NULL || length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        if (input[read_index] == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = input[read_index];
        }
    }

    if (depth != 0) {
        free(result);
        return -1;
    }

    result[write_index] = '\0';
    *output = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *temporary;

        if (length == SIZE_MAX - 1) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                new_capacity = length + 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
        capacity = 1;
    }

    if (capacity <= length) {
        char *temporary = realloc(input, length + 1);
        if (temporary == NULL) {
            free(input);
            return EXIT_FAILURE;
        }
        input = temporary;
    }

    input[length] = '\0';

    if (remove_parenthesized(input, length, &output) != 0) {
        free(input);
        fputs("Invalid input or allocation failure.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}