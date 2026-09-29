#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

static CharacterCounts count_characters(const char *string)
{
    CharacterCounts counts = {0, 0, 0};

    if (string == NULL) {
        return counts;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string++;

        if (isalpha(character)) {
            ++counts.alphabets;
        } else if (isdigit(character)) {
            ++counts.digits;
        } else {
            ++counts.special_characters;
        }
    }

    return counts;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    CharacterCounts counts = count_characters(input);

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.special_characters);

    free(input);
    return EXIT_SUCCESS;
}