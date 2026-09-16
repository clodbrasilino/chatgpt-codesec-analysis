#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_at_end(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t word_len = strlen(word);

    if (word_len == 0 || str_len < word_len) {
        return false;
    }

    size_t i = str_len;
    while (i > 0 && (ispunct((unsigned char)str[i - 1]) || isspace((unsigned char)str[i - 1]))) {
        i--;
    }

    if (i < word_len) {
        return false;
    }

    if (strncasecmp(str + i - word_len, word, word_len) != 0) {
        return false;
    }

    if (i > word_len && isalnum((unsigned char)str[i - word_len - 1])) {
        return false;
    }

    return true;
}

int main(void) {
    const char *text1 = "Hello, world!";
    const char *text2 = "This is a test.";
    const char *text3 = "The word is cat.";
    const char *text4 = "concatenate";
    const char *text5 = "A simple example";

    printf("%d\n", match_word_at_end(text1, "world"));
    printf("%d\n", match_word_at_end(text2, "test"));
    printf("%d\n", match_word_at_end(text3, "cat"));
    printf("%d\n", match_word_at_end(text4, "cat"));
    printf("%d\n", match_word_at_end(text5, "example"));
    printf("%d\n", match_word_at_end(text5, "ample"));

    return 0;
}