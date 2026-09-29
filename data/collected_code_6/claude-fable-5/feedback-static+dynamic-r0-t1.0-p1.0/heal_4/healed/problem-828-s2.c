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

    if (str == NULL || counts == NULL || max_len == 0) {
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

int read_line(char *buffer, size_t size)
{
    size_t len;
    int ch;

    if (buffer == NULL || size == 0) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    return 0;
}

int main(void)
{
    char input[MAX_LEN];
    CharCounts counts;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    if (read_line(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (count_characters(input, sizeof(input), &counts) != 0) {
        fprintf(stderr, "Error counting characters\n");
        return EXIT_FAILURE;
    }

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.specials);

    return EXIT_SUCCESS;
}