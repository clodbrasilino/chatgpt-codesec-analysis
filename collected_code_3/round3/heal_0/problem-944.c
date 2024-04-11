#include <stdio.h>
#include <ctype.h>
#include <string.h>

void printNumbersAndPositions(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(isdigit(str[i])) {
            printf("Number: %c, Position: %d\n", str[i], i);
        }
    }
}

int main() {
    char str[] = "Hello123World456";
    printNumbersAndPositions(str);
    return 0;
}