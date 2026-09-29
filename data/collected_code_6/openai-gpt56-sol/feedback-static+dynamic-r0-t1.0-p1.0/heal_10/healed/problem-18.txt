#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static void remove_characters(char *string, const char *characters)
{
    const unsigned char *source;
    unsigned char *destination;

    if (string == NULL || characters == NULL) {
        return;
    }

    source = (const unsigned char *)string;
    destination = (unsigned char *)string;

    while (*source != '\0') {
        if (strchr(characters, (int)*source) == NULL) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

static void trim_line_ending(char *string, ssize_t *length)
{
    if (string == NULL || length == NULL || *length < 0) {
        return;
    }

    while (*length > 0 &&
           (string[*length - 1] == '\n' || string[*length - 1] == '\r')) {
        string[--(*length)] = '\0';
    }
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_capacity = 0;
    size_t second_capacity = 0;
    ssize_t first_length;
    ssize_t second_length;
    int status = EXIT_FAILURE;

    first_length = getline(&first, &first_capacity, stdin);
    if (first_length < 0) {
        goto cleanup;
    }

    second_length = getline(&second, &second_capacity, stdin);
    if (second_length < 0) {
        goto cleanup;
    }

    trim_line_ending(first, &first_length);
    trim_line_ending(second, &second_length);
    remove_characters(first, second);

    if (puts(first) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}