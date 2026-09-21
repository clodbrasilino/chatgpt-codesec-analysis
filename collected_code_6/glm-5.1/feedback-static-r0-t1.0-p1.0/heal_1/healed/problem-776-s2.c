#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int count_chars_with_vowel_neighbors(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (str[len] != '\0' && len < ((size_t)-1)) {
        len++;
    }

    int count = 0;

    if (len < 2) {
        return 0;
    }

    if (is_vowel(str[1])) {
        count++;
    }

    for (size_t i = 1; i < len - 1; i++) {
        if (is_vowel(str[i - 1]) || is_vowel(str[i + 1])) {
            count++;
        }
    }

    if (is_vowel(str[len - 2])) {
        count++;
    }

    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = count_chars_with_vowel_neighbors(argv[1]);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}