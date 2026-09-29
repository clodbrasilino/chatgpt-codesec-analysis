#include <stdio.h>
#include <ctype.h>

static int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (!is_vowel(str[i])) {
            int left_vowel = (i > 0) && is_vowel(str[i - 1]);
            int right_vowel = (str[i + 1] != '\0') && is_vowel(str[i + 1]);
            
            if (left_vowel || right_vowel) {
                count++;
            }
        }
        i++;
    }

    return count;
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "abcdef";
    const char *test3 = "aeiou";
    const char *test4 = "xyz";

    printf("%d\n", count_chars_with_vowel_neighbors(test1));
    printf("%d\n", count_chars_with_vowel_neighbors(test2));
    printf("%d\n", count_chars_with_vowel_neighbors(test3));
    printf("%d\n", count_chars_with_vowel_neighbors(test4));

    return 0;
}