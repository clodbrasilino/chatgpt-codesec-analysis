#include <stdio.h>
#include <string.h>
#include <ctype.h>

void moveNumbersToString(char* str, char* numStr) {
    int i, j = 0;
    int len = strlen(str);

    for(i = 0; i < len; i++) {
        if(isdigit(str[i])) {
            numStr[j++] = str[i];
        }
    }
    numStr[j] = '\0';
}

int main() {
    char str[] = "abc123def456";
    char numStr[20];

    moveNumbersToString(str, numStr);

    printf("The numbers in the string are: %s\n", numStr);

    return 0;
}