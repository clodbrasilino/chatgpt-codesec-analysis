#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isLengthEven(const char *word) {
    
    size_t length = strlen(word);
    
    return (length % 2 == 0);
}

int main() {
    
    char word[100];
    
    printf("Enter a word: ");
    scanf("%99s", word);
    
    if(isLengthEven(word)) {
        printf("Length of the word is even.\n");
    } else {
        printf("Length of the word is odd.\n");
    }
    
    return 0;
}