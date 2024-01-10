#include <stdio.h>
#include <string.h>

#define MAX_SIZE 200

int getLengthOfLongestWord(const char* str) {
    int maxLength = 0;
    int length = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ') {
            length++;
        } else {
            if (length > maxLength) {
                maxLength = length;
            }
            length = 0;
        }
    }

    if (length > maxLength) {
        maxLength = length;
    }

    return maxLength;
}

int main() {
    char str[MAX_SIZE] = {0};

    printf("Enter a sentence: ");
    if(fgets(str, sizeof(str), stdin) != NULL){
        str[strlen(str) - 1] = '\0'; /* Remove newline character from user input */
        int length = getLengthOfLongestWord(str);
        printf("Length of the longest word is %d\n", length);
    }

    return 0;
}