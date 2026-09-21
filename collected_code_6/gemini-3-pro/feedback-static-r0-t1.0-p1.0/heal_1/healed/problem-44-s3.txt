#include <stdio.h>
#include <stdbool.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    if (*word == '\0') {
        return true;
    }

    size_t i = 0;
    while (word[i] != '\0') {
        if (str[i] != word[i]) {
            return false;
        }
        i++;
    }

    if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\0') {
        return true;
    }

    return false;
}

int main(void) {
    const char *text1 = "hello world";
    const char *word1 = "hello";
    
    if (match_word_at_beginning(text1, word1)) {
        printf("Match found.\n");
    } else {
        printf("No match.\n");
    }

    const char *text2 = "helloworld";
    
    if (match_word_at_beginning(text2, word1)) {
        printf("Match found.\n");
    } else {
        printf("No match.\n");
    }

    return 0;
}