#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool find_most_common_character(const char *string,
                                       unsigned char *character,
                                       size_t *count)
{
    size_t frequency_count;
    size_t *frequencies;
    size_t highest_count = 0;
    unsigned char most_common = 0;

    if (string == NULL || character == NULL || count == NULL ||
        string[0] == '\0') {
        return false;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    frequency_count = (size_t)UCHAR_MAX + 1;

    if (frequency_count > SIZE_MAX / sizeof(*frequencies)) {
        return false;
    }

    frequencies = calloc(frequency_count, sizeof(*frequencies));
    if (frequencies == NULL) {
        return false;
    }

    for (const unsigned char *current = (const unsigned char *)string;
         *current != '\0';
         ++current) {
        const size_t index = (size_t)*current;

        if (index >= frequency_count || frequencies[index] == SIZE_MAX) {
            free(frequencies);
            return false;
        }

        ++frequencies[index];

        if (frequencies[index] > highest_count) {
            highest_count = frequencies[index];
            most_common = *current;
        }
    }

    free(frequencies);

    *character = most_common;
    *count = highest_count;

    return true;
}

int main(int argc, char *argv[const])
{
    unsigned char character;
    size_t count;
    const char *program_name = "program";

    if (argv != NULL && argc > 0 && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "The string must not be empty.\n");
        return EXIT_FAILURE;
    }

    if (!find_most_common_character(argv[1], &character, &count)) {
        fprintf(stderr, "Unable to analyze the string.\n");
        return EXIT_FAILURE;
    }

    printf("Most common character: %c\n", (int)character);
    printf("Count: %zu\n", count);

    return EXIT_SUCCESS;
}