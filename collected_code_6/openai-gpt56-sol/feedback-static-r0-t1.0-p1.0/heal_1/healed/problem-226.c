#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_odd_indices(char *string)
{
    size_t read_index;
    size_t write_index = 0;

    if (string == NULL) {
        return;
    }

    for (read_index = 0; string[read_index] != '\0'; read_index += 2) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    remove_odd_indices(input);

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}