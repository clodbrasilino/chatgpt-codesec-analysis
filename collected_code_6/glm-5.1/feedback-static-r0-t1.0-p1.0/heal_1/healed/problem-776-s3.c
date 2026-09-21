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

    int count = 0;
    size_t i = 0;
    char prev = '\0';
    char curr = str[i];
    char next = str[i + 1];

    while (curr != '\0') {
        if (!is_vowel(curr)) {
            if (is_vowel(prev) || is_vowel(next)) {
                count++;
            }
        }
        prev = curr;
        curr = next;
        next = str[++i + 1];
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