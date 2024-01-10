#include<stdio.h>
#include<string.h>

int isWordLengthEven(const char *word) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
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