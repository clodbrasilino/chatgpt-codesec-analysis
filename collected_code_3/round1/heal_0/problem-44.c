#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_word(const char *str, const char *word) {
    int len_word = strlen(word);
    int len_str = strlen(str);

    if (len_word > len_str) {
        return false;
    }

    for (int i = 0; i < len_word; i++) {
        if (str[i] != word[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    const char *str = "Hello World";
    const char *word = "Hello";

    if (match_word(str, word)) {
        printf("Match found\n");
    } else {
        printf("Match not found\n");
    }

    return 0;
}