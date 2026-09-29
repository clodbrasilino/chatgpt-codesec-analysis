#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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

static char *reverse_vowels(char *s)
{
    size_t left;
    size_t right;
    size_t len;

    if (s == NULL) {
        return NULL;
    }

    len = strlen(s);
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
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (reverse_vowels(buffer) == NULL) {
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}