#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    char lower_c = tolower(c);
    return (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || lower_c == 'o' || lower_c == 'u');
}

int count_vowel_neighbors(const char *str) {
    int count = 0;
    int len = strlen(str);

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
    int result = count_vowel_neighbors(str);
    printf("Count of characters with vowel neighbors: %d\n", result);
    return 0;
}