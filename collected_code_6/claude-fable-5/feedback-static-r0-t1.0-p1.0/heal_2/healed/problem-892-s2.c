#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1024

void remove_multiple_spaces(char *str)
{
    size_t read_index = 0;
    size_t write_index = 0;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_index] != '\0') {
        if (str[read_index] == ' ') {
            if (previous_was_space == 0) {
                str[write_index] = str[read_index];
                write_index++;
            }
            previous_was_space = 1;
        } else {
            str[write_index] = str[read_index];
            write_index++;
            previous_was_space = 0;
        }
        read_index++;
    }

    str[write_index] = '\0';
}

int main(void)
{
    static const char input[] = "This   is  a    string   with     multiple spaces";
    char *buffer = NULL;
    size_t input_length = 0;
    size_t buffer_size = 0;
    int written = 0;

    input_length = strnlen(input, MAX_INPUT_LENGTH);
    if (input_length >= MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    buffer_size = input_length + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    written = snprintf(buffer, buffer_size, "%s", input);
    if (written < 0 || (size_t)written >= buffer_size) {
        fprintf(stderr, "String copy failed or was truncated\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Before: \"%s\"\n", buffer);
    remove_multiple_spaces(buffer);
    printf("After:  \"%s\"\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}