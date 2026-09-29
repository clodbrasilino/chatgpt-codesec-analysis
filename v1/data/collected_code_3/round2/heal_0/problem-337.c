#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_end_word(const char *str, const char *word) {
    int str_len = strlen(str);
    int word_len = strlen(word);

    if (word_len > str_len) {
        return 0;
    }

    const char *str_end = str + str_len - 1;
    const char *word_end = word + word_len - 1;

    while (word_end >= word) {
        while (!isalpha(*str_end) && str_end >= str) {
            str_end--;
        }

        if (tolower(*str_end) != tolower(*word_end)) {
            return 0;
        }

        str_end--;
        word_end--;
    }

    return 1;
}

int main() {
    printf("%d\n", match_end_word("Hello, world!", "world")); // 1
    printf("%d\n", match_end_word("Hello, world.", "world")); // 1
    printf("%d\n", match_end_word("Hello, world?", "world")); // 1
    printf("%d\n", match_end_word("Hello, world.", "hello")); // 0
    printf("%d\n", match_end_word("Hello, world!", "!"));     // 0
    printf("%d\n", match_end_word("Hello, world.", "."));     // 0

    return 0;
}