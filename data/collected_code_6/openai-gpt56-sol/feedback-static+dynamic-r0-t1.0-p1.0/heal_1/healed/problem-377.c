#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, int character)
{
    char *source;
    char *destination;

    if (string == NULL || character == EOF) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if ((unsigned char)*source != (unsigned char)character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
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

    input = fgetc(stdin);
    if (input == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    remove_character(string, input);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}