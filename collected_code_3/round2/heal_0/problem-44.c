#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_word_at_beginning(char *str, char *word) {
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
    char str[] = "Hello World";
    char word[] = "Hello";

    if (match_word_at_beginning(str, word)) {
        printf("Match found!\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}