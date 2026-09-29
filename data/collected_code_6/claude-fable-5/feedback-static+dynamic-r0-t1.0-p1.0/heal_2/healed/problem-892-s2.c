#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 256

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
    char input[] = "This   is  a    string   with     multiple spaces";
    char *buffer = NULL;
    size_t length = 0;
    size_t copy_size = 0;

    length = strnlen(input, MAX_INPUT_SIZE - 1) + 1;

    buffer = malloc(length);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    copy_size = length - 1;
    if (copy_size >= length) {
        fprintf(stderr, "Copy size exceeds destination buffer\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    memcpy(buffer, input, copy_size);
    buffer[copy_size] = '\0';

    printf("Before: \"%s\"\n", buffer);
    remove_multiple_spaces(buffer);
    printf("After:  \"%s\"\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}