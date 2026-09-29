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

static int reverse_vowels(char *s)
{
    size_t left;
    size_t right;
    size_t len;
    char tmp;

    if (s == NULL) {
        return -1;
    }

    len = strlen(s);
    if (len < 2U) {
        return 0;
    }

    left = 0U;
    right = len - 1U;

    while (left < right) {
        while ((left < right) && (!is_vowel(s[left]))) {
            left++;
        }
        while ((left < right) && (!is_vowel(s[right]))) {
            right--;
        }
        if (left < right) {
            tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            left++;
            right--;
        }
    }

    return 0;
}

int main(void)
{
    char buffer[256];
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    if (reverse_vowels(buffer) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}