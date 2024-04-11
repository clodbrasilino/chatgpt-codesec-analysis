#include <stdio.h>
#include <string.h>

int asciiValueOfString(char* str) {
    int sum = 0;
    for(int i = 0; i < strlen(str); i++) {
        sum += (int)str[i];
    }
    return sum;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    int sum = asciiValueOfString(str);
    printf("The ASCII value of total characters in the string is: %d\n", sum);
    return 0;
}