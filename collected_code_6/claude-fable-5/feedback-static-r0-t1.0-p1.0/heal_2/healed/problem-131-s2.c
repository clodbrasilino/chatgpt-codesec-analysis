#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U

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

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i = 0U;

    while ((i < max_len) && (s[i] != '\0')) {
        i++;
    }

    return i;
}

static int reverse_vowels(char *s, size_t max_len)
{
    size_t left;
    size_t right;
    size_t len;
    char tmp;

    if (s == NULL) {
        return -1;
    }

    len = bounded_strlen(s, max_len);
    if (len >= max_len) {
        return -1;
    }

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
    char buffer[BUFFER_SIZE];
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = bounded_strlen(buffer, sizeof(buffer));
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    if (reverse_vowels(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}