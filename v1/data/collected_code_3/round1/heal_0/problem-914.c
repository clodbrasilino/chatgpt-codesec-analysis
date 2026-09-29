#include <stdio.h>
#include <string.h>

int checkAlternatingCharacters(char* str) {
    int i;
    for(i = 0; i < strlen(str) - 2; i++) {
        if(str[i] != str[i+2]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    if(checkAlternatingCharacters(str)) {
        printf("The string is made up of two alternating characters.\n");
    } else {
        printf("The string is not made up of two alternating characters.\n");
    }
    return 0;
}