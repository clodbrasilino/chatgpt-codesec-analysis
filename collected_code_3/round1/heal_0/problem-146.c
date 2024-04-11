#include <stdio.h>
#include <string.h>

int asciiValue(char* str) {
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
    printf("Total ASCII value of characters: %d\n", asciiValue(str));
    return 0;
}