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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    if (reverse_vowels(buffer, sizeof(buffer)) == NULL) {
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}