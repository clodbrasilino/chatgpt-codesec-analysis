#include <ctype.h>
#include <stdio.h>
#include <string.h>

int countNumericValues(char* str) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) 
            count++;
    }
    return count;
}

int main() {
    char str[] = "Hello123World456";
    printf("Number of numeric characters in string: %d", countNumericValues(str));
    return 0;
}