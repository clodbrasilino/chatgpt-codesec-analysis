#include <stdio.h>

int countOccurrence(const char* str, char c) {
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    
    return count;
}

int main() {
    const char str[] = "Hello, World!";
    char c = 'l';
    
    int occurrence = countOccurrence(str, c);
    printf("Occurrence of '%c' in '%s' is %d\n", c, str, occurrence);
    
    return 0;
}