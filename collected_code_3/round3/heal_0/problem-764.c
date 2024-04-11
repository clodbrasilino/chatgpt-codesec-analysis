#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countNumericValues(char* str) {
    int count = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(isdigit(str[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello123";
    printf("Number of numeric values in the string: %d\n", countNumericValues(str));
    return 0;
}