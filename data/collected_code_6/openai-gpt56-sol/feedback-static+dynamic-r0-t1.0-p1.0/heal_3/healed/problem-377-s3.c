#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, unsigned char character)
{
    unsigned char *src = (unsigned char *)string;
    unsigned char *dst = (unsigned char *)string;

    while (*src != '\0') {
        if (*src != character) {
            *dst++ = *src;
        }
        ++src;
    }

    *dst = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *character_line = NULL;
    size_t character_capacity = 0;
    ssize_t character_length;
    int status = EXIT_FAILURE;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    while (length > 0 &&
           (string[length - 1] == '\n' || string[length - 1] == '\r')) {
        string[--length] = '\0';
    }

    character_length = getline(&character_line, &character_capacity, stdin);
    if (character_length < 1) {
        goto cleanup;
    }

    remove_character(string, (unsigned char)character_line[0]);

    if (fputs(string, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(character_line);
    free(string);
    return status;
}