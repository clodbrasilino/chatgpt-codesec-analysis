#include <stdio.h>
#include <stdlib.h>

int remove_multiple_spaces(char *string, size_t length)
{
    size_t read_pos = 0;
    size_t write_pos = 0;
    int previous_space = 0;

    if (string == NULL) {
        return -1;
    }

    while (read_pos < length && string[read_pos] != '\0') {
        if (string[read_pos] == ' ') {
            if (!previous_space) {
                string[write_pos++] = ' ';
                previous_space = 1;
            }
        } else {
            string[write_pos++] = string[read_pos];
            previous_space = 0;
        }

        ++read_pos;
    }

    if (read_pos == length) {
        return -1;
    }

    string[write_pos] = '\0';
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_SUCCESS;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    }

    if (remove_multiple_spaces(input, (size_t)length + 1) != 0) {
        fprintf(stderr, "Failed to process input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}