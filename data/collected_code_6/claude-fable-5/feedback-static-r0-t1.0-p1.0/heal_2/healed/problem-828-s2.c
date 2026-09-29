#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t specials;
} CharCounts;

int count_characters(const char *str, size_t max_len, CharCounts *counts)
{
    size_t i;

    if (str == NULL || counts == NULL) {
        return -1;
    }

    counts->alphabets = 0;
    counts->digits = 0;
    counts->specials = 0;

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            counts->alphabets++;
        } else if (isdigit(c)) {
            counts->digits++;
        } else if (!isspace(c)) {
            counts->specials++;
        }
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    CharCounts counts;
    size_t len;

    input = calloc(MAX_LEN, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[MAX_LEN - 1] = '\0';

    len = strnlen(input, MAX_LEN);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (count_characters(input, MAX_LEN, &counts) != 0) {
        fprintf(stderr, "Error counting characters\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.specials);

    free(input);
    return EXIT_SUCCESS;
}