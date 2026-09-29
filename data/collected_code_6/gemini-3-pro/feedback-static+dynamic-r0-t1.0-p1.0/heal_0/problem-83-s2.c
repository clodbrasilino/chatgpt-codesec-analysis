#include <stdio.h>
#include <stdlib.h>

char findAddedCharacter(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int sum = 0;
    while (*str != '\0') {
        sum += *str;
        str++;
    }

    return (char)(sum % 256);
}

int main(void) {
    const char *testString = "Hello, World!";
    
    char result = findAddedCharacter(testString);
    
    if (result != '\0') {
        printf("The character made by adding all characters is: '%c'\n", result);
    } else {
        printf("Invalid input or empty string.\n");
    }

    return 0;
}