#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matchZ(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if(str[i] == 'z' || str[i] == 'Z') {
            return true;
        }
    }
    return false;
}

int main() {
    char word[50];
    printf("Enter a word: ");
    scanf("%49s", word);
    if(matchZ(word)) {
        printf("The word contains 'z' or 'Z'.\n");
    } else {
        printf("The word does not contain 'z' or 'Z'.\n");
    }

    return 0;
}