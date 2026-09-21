#include <stdio.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int count_chars_with_vowel_neighbors(const char *str) {
    int count = 0;

    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return 0;
    }

    for (size_t i = 1; str[i + 1] != '\0'; i++) {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *test_str = "hello beautiful world";
    int result = count_chars_with_vowel_neighbors(test_str);
    printf("Result: %d\n", result);
    return 0;
}