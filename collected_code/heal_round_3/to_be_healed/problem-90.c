#include <stdio.h>
#include <string.h>

#define MAX_SIZE 200

int getLengthOfLongestWord(const char* str) {
    int maxLength = 0;
    int length = 0;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = {0};

    printf("Enter a sentence: ");
    if(fgets(str, sizeof(str), stdin) != NULL){
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        str[strlen(str) - 1] = '\0'; /* Remove newline character from user input */
        int length = getLengthOfLongestWord(str);
        printf("Length of the longest word is %d\n", length);
    }

    return 0;
}