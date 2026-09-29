#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_character(char *string, char character)
{
    char *read_ptr;
    char *write_ptr;

    if (string == NULL) {
        return;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        if (*read_ptr != character) {
            *write_ptr++ = *read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    ssize_t length;
    int input;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[--length] = '\0';
    }

    input = getchar();
    if (input == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, (char)input);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}