#include <stdio.h>
#include <string.h>

int isLengthEven(char* word) {
    int length = strlen(word);
    return length % 2 == 0;
}

int main() {
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);

    if(isLengthEven(word)) {
        printf("The length of the word is even.\n");
    } else {
        printf("The length of the word is odd.\n");
    }

    return 0;
}