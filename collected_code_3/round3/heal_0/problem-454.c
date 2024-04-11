#include <stdio.h>
#include <string.h>

int matchZ(char* word) {
    int i;
    for(i = 0; i < strlen(word); i++) {
        if(word[i] == 'z' || word[i] == 'Z') {
            return 1;
        }
    }
    return 0;
}

int main() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    if(matchZ(word)) {
        printf("The word contains 'z'.\n");
    } else {
        printf("The word does not contain 'z'.\n");
    }
    return 0;
}