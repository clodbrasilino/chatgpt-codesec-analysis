#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

static CharacterCounts count_characters(const char *string)
{
    CharacterCounts counts = {0U, 0U, 0U};

    if (string == NULL) {
        return counts;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (isalpha(character) != 0) {
            ++counts.alphabets;
        } else if (isdigit(character) != 0) {
            ++counts.digits;
        } else {
            ++counts.special_characters;
        }

        ++string;
    }

    return counts;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[(size_t)length - 1U] == '\n') {
        input[(size_t)length - 1U] = '\0';
    }

    CharacterCounts counts = count_characters(input);

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.special_characters);

    free(input);
    return EXIT_SUCCESS;
}