#include <stdio.h>

int countChar(char* str) {
    int count = 0;
    if(str != NULL) {
        while (*str != '\0') {
            count++;
            str++;
        }
    }
    return count;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%99[^\n]", str);
    int count = countChar(str);
    printf("Total characters in string: %d", count);
    return 0;
}