#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int count_characters_with_vowel_neighbors(const char *str, size_t len) {
    int count = 0;

    if (len > 1) {
        for (size_t i = 1; i < len - 1; ++i) {
            if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
                count++;
            }
        }
        if (is_vowel(str[0]) && is_vowel(str[1])) {
            count++;
        }
        if (is_vowel(str[len - 2]) && is_vowel(str[len - 1])) {
            count++;
        }
    }

    return count;
}

int main() {
    const char *test_str = "example";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(test_str);
    int result = count_characters_with_vowel_neighbors(test_str, str_len);
    printf("Count: %d\n", result);
    return 0;
}