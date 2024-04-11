#include <stdio.h>
#include <string.h>
#include <ctype.h>

void moveNumbersToString(char *str, char *numStr) {
    int i = 0, j = 0;
    while(str[i] != '\0') {
        if(isdigit(str[i])) {
            numStr[j++] = str[i];
        }
        i++;
    }
    numStr[j] = '\0';
}

int main() {
    char str[] = "abc123def456";
    char numStr[50];
    moveNumbersToString(str, numStr);
    printf("Numbers in the string: %s\n", numStr);
    return 0;
}