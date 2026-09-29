#include <stdio.h>
#include <string.h>

int match_word(char *word) {
    int len = strlen(word);
    if(len < 3) {
        return 0;
    }
    for(int i = 1; i < len - 1; i++) {
        if(word[i] == 'z') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    if(match_word(word)) {
        printf("The word contains 'z' not at the start or end.\n");
    } else {
        printf("The word does not contain 'z' not at the start or end.\n");
    }
    return 0;
}