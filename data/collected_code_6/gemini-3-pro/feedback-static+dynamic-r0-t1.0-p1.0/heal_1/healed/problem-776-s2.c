#include <stdio.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return 0;
    }

    int count = 0;
    size_t i = 1;

    while (str[i] != '\0' && str[i + 1] != '\0') {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
        i++;
    }

    return count;
}

int main(void) {
    const char *test_str = "hello beautiful world";
    int result = count_chars_with_vowel_neighbors(test_str);
    printf("Result: %d\n", result);
    return 0;
}