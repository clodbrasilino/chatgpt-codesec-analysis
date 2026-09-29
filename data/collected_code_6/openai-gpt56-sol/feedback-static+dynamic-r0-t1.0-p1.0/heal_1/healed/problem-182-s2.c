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

static int count_characters(const char *text, CharacterCounts *counts)
{
    if (text == NULL || counts == NULL) {
        return -1;
    }

    *counts = (CharacterCounts){0};

    for (const unsigned char *current = (const unsigned char *)text;
         *current != '\0';
         ++current) {
        if (isupper(*current)) {
            ++counts->uppercase;
        } else if (islower(*current)) {
            ++counts->lowercase;
        } else if (isdigit(*current)) {
            ++counts->numeric;
        } else if (!isalnum(*current) && !isspace(*current)) {
            ++counts->special;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    CharacterCounts counts;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (input[length - 1] == '\n' || input[length - 1] == '\r')) {
        input[--length] = '\0';
    }

    if (count_characters(input, &counts) != 0) {
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