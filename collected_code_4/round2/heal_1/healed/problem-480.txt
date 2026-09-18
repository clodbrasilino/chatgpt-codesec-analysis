#include <stdio.h>
#include <string.h>

#define ASCII_SIZE 256

char getMaxOccurringChar(char* str) {
    int count[ASCII_SIZE] = {0};
    int len = strlen(str);
    int max = 0; 
    char result = 0;   

    for (int i = 0; i < len; i++) {
        count[str[i]]++;
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }

    return result;
}

int main() {
    char str[] = "sample string";
    printf("Max occurring character is '%c'.\n", getMaxOccurringChar(str));
    return 0;
}