#include <stdio.h>

char* findLastOccurrence(char* str, char ch) {
    char* last = NULL;
    
    /* Possible weaknesses found:
     *  Cannot determine that '*str' is initialized [premium-bughuntingUninit]
     */
    while (*str != '\0') {
        if (*str == ch) {
            last = str;
        }
        str++;
    }
    
    return last;
}

int main() {
    char str[] = "hello";
    char ch = 'l';
    
    char* lastOccurrence = findLastOccurrence(str, ch);
    
    printf("Last occurrence of '%c' is at index %ld\n", ch, lastOccurrence - str);
    
    return 0;
}