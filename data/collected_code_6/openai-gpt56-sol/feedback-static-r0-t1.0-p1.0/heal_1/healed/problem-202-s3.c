#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int remove_even_characters(char *string, size_t length)
{
    size_t read_index;
    size_t write_index = 0;

    if (string == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; read_index += 2) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    size_t content_length;
    ssize_t input_length;

    input_length = getline(&string, &capacity, stdin);
    if (input_length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    content_length = (size_t)input_length;

    if (content_length > 0 && string[content_length - 1] == '\n') {
        --content_length;
        string[content_length] = '\0';
    }

    if (remove_even_characters(string, content_length) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}