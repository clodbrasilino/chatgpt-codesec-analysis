#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }

    int i, j, strLength = strlen(str);
    for (i = 0, j = 0; i <= strLength; i++) {
        if (str[i] == '\0' || isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
}

int main() {
    char str[MAX_SIZE] = "";
    char* newLineCheck;

    printf("Enter a string: ");
    newLineCheck = fgets(str, sizeof(str), stdin);

    if(newLineCheck != NULL && str[MAX_SIZE - 1] != '\0') {
        size_t ln = strlen(str) - 1;
        if (str[ln] == '\n') {
            str[ln] = '\0';
        }
    }

    char* strPointer = str;
    if (strPointer != NULL && *strPointer != '\0') {
        removeNonAlphanumeric(strPointer);
        printf("String after removing non-alphanumeric characters: %s\n", str);
    }

    return 0;
}