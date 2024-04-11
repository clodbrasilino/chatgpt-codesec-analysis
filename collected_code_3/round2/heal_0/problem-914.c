#include <stdio.h>
#include <string.h>

int isAlternating(char* str) {
    int i;
    char first = str[0];
    char second = str[1];

    if(first == second) {
        return 0;
    }

    for(i = 2; str[i] != '\0'; i++) {
        if(i % 2 == 0) {
            if(str[i] != first) {
                return 0;
            }
        } else {
            if(str[i] != second) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if(isAlternating(str)) {
        printf("The string is made up of two alternating characters.\n");
    } else {
        printf("The string is not made up of two alternating characters.\n");
    }

    return 0;
}