#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *duplicate_string(const char *source)
{
    size_t length = 0;
    size_t i;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    while (source[length] != '\0') {
        if (length == SIZE_MAX - 1) {
            return NULL;
        }
        ++length;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i <= length; ++i) {
        copy[i] = source[i];
    }

    return copy;
}

static int replace_with_colons(char *string)
{
    char *cursor;

    if (string == NULL) {
        return -1;
    }

    for (cursor = string; *cursor != '\0'; ++cursor) {
        if (*cursor == ' ' || *cursor == ',' || *cursor == '.') {
            *cursor = ':';
        }
    }

    return 0;
}

int main(int argc, char * const argv[])
{
    char *string;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    string = duplicate_string(argv[1]);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (replace_with_colons(string) != 0) {
        free(string);
        fputs("String processing failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}