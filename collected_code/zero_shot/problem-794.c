#include <stdio.h>

int matchString(char* str) {
    int i = 0;
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    while (i < len-2) {
        if (str[i] == 'a' && str[i + 2] == 'b') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    int result = matchString(str);
    if (result == 1) {
        printf("String matches the pattern.\n");
    } else {
        printf("String does not match the pattern.\n");
    }
    return 0;
}