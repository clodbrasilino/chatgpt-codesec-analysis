#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }
    int i, j;
    int strLength = strlen(str);
    for (i = 0, j = 0; i < strLength; i++) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    
    char str[MAX_SIZE] = "";

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    if( str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }

    char* strPointer = str;
    if (strPointer != NULL && *strPointer != '\0') {
        removeNonAlphanumeric(strPointer);
        printf("String after removing non-alphanumeric characters: %s\n", str);
    }
    
    return 0;
}