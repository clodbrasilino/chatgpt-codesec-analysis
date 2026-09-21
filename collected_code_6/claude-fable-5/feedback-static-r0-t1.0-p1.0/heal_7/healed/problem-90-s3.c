#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

size_t longest_word_length(void);

size_t longest_word_length(void)
{
    size_t max_len = 0;
    size_t current_len = 0;
    int c;

    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (isspace((unsigned char)c)) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            if (current_len < SIZE_MAX) {
                current_len++;
            }
        }
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main(void)
{
    size_t result;

    result = longest_word_length();

    if (ferror(stdin)) {
        if (fprintf(stderr, "Error reading input\n") < 0) {
            return 1;
        }
        return 1;
    }

    if (printf("Longest word length: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}