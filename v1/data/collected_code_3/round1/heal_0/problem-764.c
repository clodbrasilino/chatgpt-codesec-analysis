#include <stdio.h>
#include <string.h>

int countNumericValues(char* str) {
    int count = 0;
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello123";
    printf("Number of numeric values in the string: %d", countNumericValues(str));
    return 0;
}