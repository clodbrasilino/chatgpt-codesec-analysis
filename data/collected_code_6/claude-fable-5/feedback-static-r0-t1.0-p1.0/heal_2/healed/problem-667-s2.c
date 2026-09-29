#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

size_t count_vowels(const char *str, size_t max_len)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        int c = tolower((unsigned char)str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char *buffer;
    size_t vowel_count;
    size_t len;

    buffer = malloc(MAX_INPUT_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");

    if (fgets(buffer, MAX_INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_SIZE - 1] = '\0';

    len = strnlen(buffer, MAX_INPUT_SIZE);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    vowel_count = count_vowels(buffer, MAX_INPUT_SIZE);

    printf("Number of vowels: %zu\n", vowel_count);

    free(buffer);

    return EXIT_SUCCESS;
}