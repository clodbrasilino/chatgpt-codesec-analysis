#include <stdio.h>
#include <ctype.h>

void printNumbersAndPositions(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(isdigit(str[i])) {
            printf("Number: %c at Position: %d\n", str[i], i);
        }
    }
}

int main() {
    char str[] = "Hello123World456";
    printNumbersAndPositions(str);
    return 0;
}