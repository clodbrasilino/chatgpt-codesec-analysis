#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void set_error_message(char *buffer, size_t size, const char *message)
{
    size_t index = 0;

    if (buffer == NULL || size == 0) {
        return;
    }

    while (index + 1 < size && message[index] != '\0') {
        buffer[index] = message[index];
        ++index;
    }

    buffer[index] = '\0';
}

int remove_lowercase_substrings(char *string, char *error, size_t error_size)
{
    char *source;
    char *destination;

    if (error != NULL && error_size > 0) {
        error[0] = '\0';
    }

    if (string == NULL) {
        set_error_message(error, error_size, "Invalid string argument");
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error[256];

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

    if (remove_lowercase_substrings(string, error, sizeof(error)) != 0) {
        fprintf(stderr, "Error: %s\n", error);
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