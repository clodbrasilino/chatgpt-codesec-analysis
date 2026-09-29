#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

int match_words(char words[MAX_WORDS][MAX_WORD_LENGTH], char* word1, char* word2) {
    int i;
    for(i = 0; i < MAX_WORDS; i++) {
        if(words[i][0] != 'p') {
            continue;
        }
        if(strcmp(words[i], word1) == 0 || strcmp(words[i], word2) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {"apple", "banana", "pear", "peach", "pineapple"};
    char* word1 = "pear";
    char* word2 = "peach";

    if(match_words(words, word1, word2)) {
        printf("Match found\n");
    } else {
        printf("No match found\n");
    }

    return 0;
}