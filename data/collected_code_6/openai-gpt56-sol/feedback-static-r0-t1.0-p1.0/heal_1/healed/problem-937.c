#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *data, size_t length,
                          unsigned char *result)
{
    size_t frequencies[256] = {0};
    size_t highest_frequency = 0;
    unsigned char most_common = 0;

    if (data == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = data[i];

        if (++frequencies[character] > highest_frequency) {
            highest_frequency = frequencies[character];
            most_common = character;
        }
    }

    *result = most_common;
    return 1;
}

int main(void)
{
    unsigned char frequencies_input[1024];
    size_t length = 0;
    int character;
    unsigned char result;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length < sizeof(frequencies_input)) {
            frequencies_input[length++] = (unsigned char)character;
        }
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (!most_common_character(frequencies_input, length, &result)) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputc(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}