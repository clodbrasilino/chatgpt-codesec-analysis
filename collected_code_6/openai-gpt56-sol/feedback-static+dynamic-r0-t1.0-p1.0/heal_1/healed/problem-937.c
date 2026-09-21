#include <stdio.h>
#include <stdlib.h>

int most_common_character(const unsigned char *string, size_t length,
                          unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest_frequency = 0;
    unsigned char most_common = 0;

    if (string == NULL || result == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = string[i];

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
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t highest_frequency = 0;
    unsigned char result = 0;
    int character;
    int found = 0;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        unsigned char value = (unsigned char)character;
        found = 1;

        if (++frequencies[value] > highest_frequency) {
            highest_frequency = frequencies[value];
            result = value;
        }
    }

    if (ferror(stdin)) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    if (!found) {
        fputs("Input must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputc(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}