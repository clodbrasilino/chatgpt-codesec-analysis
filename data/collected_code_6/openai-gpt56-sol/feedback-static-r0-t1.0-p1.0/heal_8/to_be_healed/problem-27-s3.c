#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    char *read_pos;
    char *write_pos;

    if (string == NULL) {
        return;
    }

    read_pos = string;
    write_pos = string;

    while (*read_pos != '\0') {
        unsigned char character = (unsigned char)*read_pos++;

        if (!isdigit(character)) {
            *write_pos++ = (char)character;
        }
    }

    *write_pos = '\0';
}

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

int main(int argc, char *argv[])
{
    char **strings;
    size_t count;
    size_t initialized = 0U;
    size_t i;
    int status = EXIT_SUCCESS;

    if (argc <= 1) {
        return EXIT_SUCCESS;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*strings)) {
        return EXIT_FAILURE;
    }

    strings = calloc(count, sizeof(*strings));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        const char *argument = argv[i + 1];
        size_t length;

        if (argument == NULL) {
            status = EXIT_FAILURE;
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(argument);

        strings[i] = duplicate_string(argument, length);
        if (strings[i] == NULL) {
            status = EXIT_FAILURE;
            break;
        }

        ++initialized;
        remove_digits(strings[i]);
    }

    if (status == EXIT_SUCCESS) {
        for (i = 0U; i < count; ++i) {
            if (puts(strings[i]) == EOF) {
                status = EXIT_FAILURE;
                break;
            }
        }
    }

    for (i = 0U; i < initialized; ++i) {
        free(strings[i]);
    }

    free(strings);
    return status;
}