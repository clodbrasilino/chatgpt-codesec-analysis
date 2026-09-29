#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_end_word(const char *str, const char *word) {
    int str_len = strlen(str);
    int word_len = strlen(word);

    if (word_len > str_len) {
        return 0;
    }

    str += str_len - word_len;

    if (strncmp(str, word, word_len) == 0) {
        if (str_len == word_len || isspace(*(str - 1)) || ispunct(*(str - 1))) {
            return 1;
        }
    }

    return 0;
}

int main() {
    printf("%d\n", match_end_word("Hello, world!", "world!")); // 1
    printf("%d\n", match_end_word("Hello, world.", "world")); // 0
    printf("%d\n", match_end_word("Hello, world.", "world.")); // 1
    printf("%d\n", match_end_word("Hello, world", "world")); // 1
    printf("%d\n", match_end_word("Hello, world", "hello")); // 0

    return 0;
}