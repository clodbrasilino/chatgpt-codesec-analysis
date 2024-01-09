#include <stdio.h>
#include <string.h>

int countSubstrings(char* str) {
    int length = strlen(str);
    int count = 0;
    
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            count++;
        }
    }
    
    return count;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%[^\n]", str);
    
    int result = countSubstrings(str);
    printf("Number of non-empty substrings: %d\n", result);
    
    return 0;
}