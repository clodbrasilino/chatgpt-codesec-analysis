#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

int count_vowel_neighbors(const char *str, int len) {
    int count = 0;

    for (int i = 1; i < len - 1; ++i) {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
    }

    if (len > 1 && is_vowel(str[0]) && is_vowel(str[1])) {
        count++;
    }

    if (len > 1 && is_vowel(str[len - 2]) && is_vowel(str[len - 1])) {
        count++;
    }

    return count;
}

int main() {
    const char *str = "beautiful";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int result = count_vowel_neighbors(str, strlen(str));
    printf("Count of characters with vowel neighbors: %d\n", result);
    return 0;
}