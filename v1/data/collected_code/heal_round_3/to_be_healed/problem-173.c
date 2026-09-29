#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }
    int i, j;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int strLength = strlen(str);
    for (i = 0, j = 0; i < strLength; i++) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE] = "";

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if( str[strlen(str)-1] == '\n') {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        str[strlen(str)-1] = '\0';
    }

    char* strPointer = str;
    if (strPointer != NULL && *strPointer != '\0') {
        removeNonAlphanumeric(strPointer);
        printf("String after removing non-alphanumeric characters: %s\n", str);
    }
    
    return 0;
}