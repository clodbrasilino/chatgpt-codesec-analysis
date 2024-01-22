#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 100

void removeMultipleSpaces(char *str) {
    size_t length = strnlen(str, MAX_STR_SIZE);
    int lastCharSpaceFlag = 0, currentCharSpaceFlag = 0;
    char newStr[MAX_STR_SIZE + 1] = { 0 };
    int i = 0, j = 0;

    if (length > MAX_STR_SIZE) {
        length = MAX_STR_SIZE;
    }

    for (i = 0; i < length; i++) {
        currentCharSpaceFlag = (str[i] == ' ') ? 1 : 0;

        if ( !(lastCharSpaceFlag && currentCharSpaceFlag) ) {
            newStr[j++] = str[i];
        }

        lastCharSpaceFlag = currentCharSpaceFlag;
    }
    newStr[j] = '\0';

    strncpy(str, newStr, MAX_STR_SIZE + 1);
}

int main() {
    char str[MAX_STR_SIZE + 1] = { 0 };

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    removeMultipleSpaces(str);

    printf("String after removing multiple spaces: %s\n", str);

    return 0;
}
