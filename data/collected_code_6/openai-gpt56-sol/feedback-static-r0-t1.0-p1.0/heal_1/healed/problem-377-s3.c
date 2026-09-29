#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_character(char *string, char character)
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
    char *character_line = NULL;
    size_t string_capacity = 0U;
    size_t character_capacity = 0U;
    ssize_t string_length;
    ssize_t character_length;
    int status = EXIT_FAILURE;

    string_length = getline(&string, &string_capacity, stdin);
    if (string_length < 0) {
        goto cleanup;
    }

    if (string_length > 0 && string[string_length - 1] == '\n') {
        string[--string_length] = '\0';
    }

    if (string_length > 0 && string[string_length - 1] == '\r') {
        string[--string_length] = '\0';
    }

    character_length = getline(&character_line, &character_capacity, stdin);
    if (character_length < 1 ||
        character_line[0] == '\n' ||
        character_line[0] == '\r') {
        goto cleanup;
    }

    remove_character(string, character_line[0]);

    if (puts(string) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(character_line);
    free(string);
    return status;
}