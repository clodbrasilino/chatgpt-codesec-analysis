#include <stdio.h>
#include <string.h>

int isLengthOdd(char* word) {
    int length = strlen(word);
    return length % 2;
}

int main() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    if(isLengthOdd(word)) {
        printf("The length of the word is odd.\n");
    } else {
        printf("The length of the word is even.\n");
    }
    return 0;
}