#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_lowercase_substrings(char *string, const char **error)
{
    char *source;
    char *destination;

    if (error != NULL) {
        *error = NULL;
    }

    if (string == NULL) {
        if (error != NULL) {
            *error = "Invalid string argument";
        }
        return -1;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;

        if (character < (unsigned char)'a' ||
            character > (unsigned char)'z') {
            *destination++ = (char)character;
        }
    }

    *destination = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    char *string;
    const char *error = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    string = strdup(argv[1]);
    if (string == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        return EXIT_FAILURE;
    }

    if (remove_lowercase_substrings(string, &error) != 0) {
        fprintf(stderr, "Error: %s\n",
                error != NULL ? error : "Unknown error");
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        fprintf(stderr, "Unable to write output\n");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}