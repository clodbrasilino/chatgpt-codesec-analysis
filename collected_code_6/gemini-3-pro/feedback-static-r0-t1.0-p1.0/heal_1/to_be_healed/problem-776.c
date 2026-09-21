#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    char lower_c = tolower((unsigned char)c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 3) {
        return 0;
    }

    int count = 0;
    for (size_t i = 1; i < len - 1; i++) {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *test_str = "abacaedo";
    int result = count_chars_with_vowel_neighbors(test_str);
    printf("%d\n", result);
    return 0;
}