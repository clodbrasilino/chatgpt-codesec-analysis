#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 256U

static bool is_vowel(char c)
{
    switch (c) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
    case 'A': case 'E': case 'I': case 'O': case 'U':
        return true;
    default:
        return false;
    }
}

static char *reverse_vowels(char *s, size_t max_len)
{
    size_t left;
    size_t right;
    size_t len;

    if (s == NULL || max_len == 0U) {
        return NULL;
    }

    len = strnlen(s, max_len);
    if (len >= max_len) {
        return NULL;
    }

    if (len < 2U) {
        return s;
    }

    left = 0U;
    right = len - 1U;

    while (left < right) {
        if (!is_vowel(s[left])) {
            left++;
        } else if (!is_vowel(s[right])) {
            right--;
        } else {
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            left++;
            right--;
        }
    }

    return s;
}

int main(void)
{
    char *buffer;

    buffer = calloc(MAX_INPUT_LEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_LEN - 1U] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (reverse_vowels(buffer, MAX_INPUT_LEN) == NULL) {
        fprintf(stderr, "Invalid string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}