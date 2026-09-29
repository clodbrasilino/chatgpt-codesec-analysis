#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, unsigned char character)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        unsigned char current = (unsigned char)*source++;

        if (current != character) {
            *destination++ = (char)current;
        }
    }

    *destination = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    unsigned char character;
    int result = EXIT_FAILURE;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[--length] = '\0';

        if (length > 0 && string[length - 1] == '\r') {
            string[--length] = '\0';
        }
    }

    if (fread(&character, sizeof character, 1, stdin) != 1) {
        goto cleanup;
    }

    remove_character(string, character);

    if (puts(string) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(string);
    return result;
}