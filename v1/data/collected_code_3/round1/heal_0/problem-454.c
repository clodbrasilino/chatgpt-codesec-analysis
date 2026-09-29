#include <stdio.h>
#include <string.h>

int containsZ(char* word) {
    int length = strlen(word);
    for(int i = 0; i < length; i++) {
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
    if(containsZ(word)) {
        printf("The word contains 'z' or 'Z'.\n");
    } else {
        printf("The word does not contain 'z' or 'Z'.\n");
    }
    return 0;
}