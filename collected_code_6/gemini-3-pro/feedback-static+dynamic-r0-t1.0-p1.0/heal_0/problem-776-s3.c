#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    int count = 0;

    if (len < 3) {
        return 0;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (is_vowel(str[i - 1]) && is_vowel(str[i + 1])) {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *test1 = "abaca";
    const char *test2 = "hello";
    const char *test3 = "aeb";
    const char *test4 = NULL;

    printf("%d\n", count_chars_with_vowel_neighbors(test1));
    printf("%d\n", count_chars_with_vowel_neighbors(test2));
    printf("%d\n", count_chars_with_vowel_neighbors(test3));
    printf("%d\n", count_chars_with_vowel_neighbors(test4));

    return 0;
}