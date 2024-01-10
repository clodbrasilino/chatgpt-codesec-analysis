#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 256

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }
    int i, j;
    for (i = 0, j = 0; i < strlen(str); i++) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_SIZE];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    if( str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }
    removeNonAlphanumeric(str);
    printf("String after removing non-alphanumeric characters: %s", str);
    return 0;
}