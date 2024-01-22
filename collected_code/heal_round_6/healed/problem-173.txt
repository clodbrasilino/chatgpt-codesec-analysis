#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }

    for (int i = 0, j = 0; str[i] != '\0'; i++) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        } 
        str[j] = '\0';
    }
}

int main() {
    char str[MAX_SIZE] = " ";
    char* newLineCheck;
    
    printf("Enter a string: ");
    newLineCheck = fgets(str, sizeof(str), stdin);

    if(newLineCheck != NULL) {
        if(str[strlen(str)-1] != '\n' && strlen(str) < MAX_SIZE) {
            str[strlen(str)] = '\0';
        }
        
        int ln = strlen(str) - 1;
        if (str[ln] == '\n') {
            str[ln] = '\0';
        }
    }

    if (str != NULL && str[0] != '\0') {
        removeNonAlphanumeric(str);
        printf("String after removing non-alphanumeric characters: %s\n", str);
    }

    return 0;
}