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

    if (strcasecmp(str, word) == 0) {
        return 1;
    }

    if (word_len < str_len && ispunct((unsigned char)str[-1]) && strcasecmp(str - 1, word) == 0) {
        return 1;
    }

    return 0;
}

int main() {
    printf("%d\n", match_end_word("Hello, world!", "world!"));
    printf("%d\n", match_end_word("Hello, world.", "world"));
    printf("%d\n", match_end_word("Hello, world.", "World"));
    printf("%d\n", match_end_word("Hello, world.", "hello"));
    return 0;
}