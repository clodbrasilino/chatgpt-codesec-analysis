#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void remove_characters(char *string, const char *characters)
{
    unsigned char remove_table[UCHAR_MAX + 1] = {0};
    unsigned char *source;
    unsigned char *destination;

    if (string == NULL || characters == NULL) {
        return;
    }

    while (*characters != '\0') {
        remove_table[(unsigned char)*characters++] = 1;
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

static void remove_trailing_newline(char *string, ssize_t length)
{
    size_t position;

    if (string == NULL || length <= 0) {
        return;
    }

    position = (size_t)length - 1;

    if (string[position] == '\n') {
        string[position] = '\0';

        if (position > 0 && string[position - 1] == '\r') {
            string[position - 1] = '\0';
        }
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