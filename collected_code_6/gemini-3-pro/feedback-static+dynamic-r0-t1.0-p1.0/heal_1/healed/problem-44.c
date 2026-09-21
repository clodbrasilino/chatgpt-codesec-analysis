#include <stdio.h>
#include <stdbool.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    if (*word == '\0') {
        return false;
    }

    const char *s = str;
    const char *w = word;

    while (*w != '\0') {
        if (*s == '\0' || *s != *w) {
            return false;
        }
        s++;
        w++;
    }

    if (*s == ' ' || *s == '\0' || *s == '\t' || *s == '\n') {
        return true;
    }

    return false;
}

int main(void) {
    const char *text1 = "hello world";
    const char *text2 = "helloworld";
    const char *word = "hello";

    if (match_word_at_beginning(text1, word)) {
        printf("Matched '%s' in '%s'\n", word, text1);
    } else {
        printf("Did not match '%s' in '%s'\n", word, text1);
    }

    if (match_word_at_beginning(text2, word)) {
        printf("Matched '%s' in '%s'\n", word, text2);
    } else {
        printf("Did not match '%s' in '%s'\n", word, text2);
    }

    return 0;
}