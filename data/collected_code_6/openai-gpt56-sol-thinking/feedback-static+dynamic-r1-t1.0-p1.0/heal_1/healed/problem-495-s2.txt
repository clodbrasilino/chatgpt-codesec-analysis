#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void set_error_message(char *buffer, size_t size, const char *message)
{
    size_t index = 0;

    if (buffer == NULL || size == 0) {
        return;
    }

    while (index < size - 1 && message[index] != '\0') {
        buffer[index] = message[index];
        ++index;
    }

    buffer[index] = '\0';
}

int remove_lowercase_substrings(char *string, char *error, size_t error_size)
{
    char *source;
    char *destination;

    if (string == NULL) {
        set_error_message(error, error_size, "Invalid string argument");
        return -1;
    }

    if (error != NULL && error_size > 0) {
        error[0] = '\0';
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if (*source < 'a' || *source > 'z') {
            *destination++ = *source;
        }

        ++source;
    }

    *destination = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_lowercase_substrings(argv[1], NULL, 0) != 0) {
        fprintf(stderr, "Unable to process input\n");
        return EXIT_FAILURE;
    }

    puts(argv[1]);
    return EXIT_SUCCESS;
}