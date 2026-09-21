#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static void remove_characters(char *string, const char *characters)
{
    unsigned char remove_table[256] = {0};
    unsigned char *source;
    unsigned char *destination;

    if (string == NULL || characters == NULL) {
        return;
    }

    while (*characters != '\0') {
        remove_table[(unsigned char)*characters] = 1;
        ++characters;
    }

    source = (unsigned char *)string;
    destination = (unsigned char *)string;

    while (*source != '\0') {
        if (remove_table[*source] == 0) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

static void remove_trailing_newline(char *string, size_t length)
{
    if (string == NULL || length == 0) {
        return;
    }

    if (string[length - 1] == '\n') {
        string[--length] = '\0';

        if (length != 0 && string[length - 1] == '\r') {
            string[length - 1] = '\0';
        }
    }
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_capacity = 0;
    size_t second_capacity = 0;
    ssize_t result;
    size_t first_length;
    size_t second_length;
    int status = EXIT_FAILURE;

    result = getline(&first, &first_capacity, stdin);
    if (result < 0) {
        goto cleanup;
    }
    first_length = (size_t)result;

    result = getline(&second, &second_capacity, stdin);
    if (result < 0) {
        goto cleanup;
    }
    second_length = (size_t)result;

    remove_trailing_newline(first, first_length);
    remove_trailing_newline(second, second_length);
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