#include <stdio.h>
#include <string.h>

int isBinary(char* str) {
    int i, length = strlen(str);

    for(i = 0; i < length; i++) {
        if(str[i] != '0' && str[i] != '1') {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if(isBinary(str)) {
        printf("The string is a binary string.\n");
    } else {
        printf("The string is not a binary string.\n");
    }

    return 0;
}