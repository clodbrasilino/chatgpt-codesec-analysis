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

int count_characters(const char *str, CharCounts *counts)
{
    size_t i;

    if (str == NULL || counts == NULL) {
        return -1;
    }

    counts->alphabets = 0;
    counts->digits = 0;
    counts->specials = 0;

    for (i = 0; str[i] != '\0'; i++) {
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
    char input[MAX_LEN];
    CharCounts counts;
    size_t len;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (count_characters(input, &counts) != 0) {
        fprintf(stderr, "Error counting characters\n");
        return EXIT_FAILURE;
    }

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.specials);

    return EXIT_SUCCESS;
}