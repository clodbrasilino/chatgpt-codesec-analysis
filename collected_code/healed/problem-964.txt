#include<stdio.h>
#include<string.h>

int isWordLengthEven(const char *word) {
    if (word == NULL) {
        return 0;
    }
    int length = strlen(word);
    if(length % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *word = "programming";
    if(isWordLengthEven(word)) {
        printf("The word length is even.\n");
    } else {
        printf("The word length is odd.\n");
    }
    return 0;
}