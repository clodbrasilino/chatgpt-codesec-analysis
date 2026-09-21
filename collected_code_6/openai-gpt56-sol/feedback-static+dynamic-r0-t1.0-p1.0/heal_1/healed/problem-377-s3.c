#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, int character)
{
    char *read_ptr;
    char *write_ptr;

    if (string == NULL || character == EOF) {
        return;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        if ((unsigned char)*read_ptr != (unsigned char)character) {
            *write_ptr++ = *read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    int character;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[--length] = '\0';
        if (length > 0 && string[length - 1] == '\r') {
            string[--length] = '\0';
        }
    }

    character = fgetc(stdin);
    if (character == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, character);

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}