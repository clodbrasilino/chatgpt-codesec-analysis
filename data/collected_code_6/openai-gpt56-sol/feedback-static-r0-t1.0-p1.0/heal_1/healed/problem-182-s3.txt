#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct {
    size_t uppercase;
    size_t lowercase;
    size_t numeric;
    size_t special;
} CharacterCounts;

static int count_character_types(const char *input, size_t length,
                                 CharacterCounts *counts)
{
    size_t i;

    if (input == NULL || counts == NULL) {
        return -1;
    }

    counts->uppercase = 0;
    counts->lowercase = 0;
    counts->numeric = 0;
    counts->special = 0;

    for (i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)input[i];

        if (character >= 'A' && character <= 'Z') {
            ++counts->uppercase;
        } else if (character >= 'a' && character <= 'z') {
            ++counts->lowercase;
        } else if (character >= '0' && character <= '9') {
            ++counts->numeric;
        } else {
            ++counts->special;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t input_length;
    ssize_t length;
    CharacterCounts counts;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    input_length = (size_t)length;

    if (input_length > 0 && input[input_length - 1] == '\n') {
        --input_length;
    }

    if (input_length > 0 && input[input_length - 1] == '\r') {
        --input_length;
    }

    if (count_character_types(input, input_length, &counts) != 0) {
        free(input);
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Uppercase: %zu\n", counts.uppercase);
    printf("Lowercase: %zu\n", counts.lowercase);
    printf("Numeric: %zu\n", counts.numeric);
    printf("Special: %zu\n", counts.special);

    free(input);
    return EXIT_SUCCESS;
}