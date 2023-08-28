#include <stdio.h>

// Function to check if a number is present at the end of a string
int checkNumberAtEnd(char* string) {
    int i = 0;
    
    // Loop through the string until the end
    while (string[i] != '\0') {
        i++;
    }
    
    // Decrement i to check the last character
    i--;
    
    // Check if the last character is a digit
    if (string[i] >= '0' && string[i] <= '9') {
        return 1; // Number is present at the end
    } else {
        return 0; // Number is not present at the end
    }
}

int main() {
    char str1[] = "Hello World123";
    char str2[] = "Hello123";
    
    printf("String 1: %s\n", checkNumberAtEnd(str1) ? "Number is present at the end" : "Number is not present at the end");
    printf("String 2: %s\n", checkNumberAtEnd(str2) ? "Number is present at the end" : "Number is not present at the end");
    
    return 0;
}