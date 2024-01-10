#include <stdio.h>

int checkNumberAtEnd(const char* string) {
    int i = 0;    
    while (string[i] != '\0') {
        i++;
    }    
    i--;    
    if (string[i] >= '0' && string[i] <= '9') {
        return 1; 
    } else {
        return 0; 
    }
}

int main() {
    const char str1[] = "Hello World123";
    const char str2[] = "Hello123";
    
    printf("String 1: %s\n", checkNumberAtEnd(str1) ? "Number is present at the end" : "Number is not present at the end");
    printf("String 2: %s\n", checkNumberAtEnd(str2) ? "Number is present at the end" : "Number is not present at the end");
    
    return 0;
}