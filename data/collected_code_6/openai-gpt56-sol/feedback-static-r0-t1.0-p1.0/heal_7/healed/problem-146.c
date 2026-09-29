#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int print_ascii_values(const unsigned char *string, size_t length)
{
    if (string == NULL && length != 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%u\n", (unsigned int)string[i]) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    unsigned char string[MAX_INPUT_LENGTH];
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= sizeof string) {
            fprintf(stderr, "Input exceeds maximum length\n");
            return EXIT_FAILURE;
        }

        string[length++] = (unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        return EXIT_FAILURE;
    }

    if (print_ascii_values(string, length) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}