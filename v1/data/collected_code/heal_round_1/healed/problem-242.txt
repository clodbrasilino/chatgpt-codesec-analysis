#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

int countCharacters(char *str) {
    if(!str) return 0;
    
    int count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }   
    return count;
}

int main() {
    char *str = malloc(MAX_LEN);
    if(!str) return 1;
    
    printf("Enter a string: ");
    if(!fgets(str, MAX_LEN, stdin)) return 1;
    
    str[strcspn(str, "\n")] = '\0';
    
    int totalCharacters = countCharacters(str);

    printf("Total characters in the string: %d", totalCharacters);

    free(str);
    
    return 0;
}