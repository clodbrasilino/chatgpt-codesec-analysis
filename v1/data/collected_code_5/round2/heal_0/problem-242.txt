#include <stdio.h>
#include <string.h>

int count_chars(char* str) {
    int count = 0;

    if(str != NULL) {
        while(*str != '\0') {
            count++;
            str++;
        }
    }

    return count;
}

int main() {
    char test[] = "Sample String";
    
    printf("Total Characters: %d\n", count_chars(test));
    
    return 0;
}