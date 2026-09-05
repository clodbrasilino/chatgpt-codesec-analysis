#include <stdio.h>
#include <string.h>

void replaceMultipleOccurrences(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    
    size_t read = 0;
    size_t write = 0;
    
    while (str[read] != '\0') {
        str[write++] = str[read];
        
        if (str[read] == ch) {
            while (str[read] == ch) {
                read++;
            }
        } else {
            read++;
        }
    }
    
    str[write] = '\0';
}

int main(void) {
    char str1[] = "aaabbbcccdddaaa";
    char str2[] = "hello world";
    char str3[] = "aaaa";
    char str4[] = "no duplicates";
    
    printf("Before: %s\n", str1);
    replaceMultipleOccurrences(str1, 'a');
    printf("After:  %s\n\n", str1);
    
    printf("Before: %s\n", str2);
    replaceMultipleOccurrences(str2, 'l');
    printf("After:  %s\n\n", str2);
    
    printf("Before: %s\n", str3);
    replaceMultipleOccurrences(str3, 'a');
    printf("After:  %s\n\n", str3);
    
    printf("Before: %s\n", str4);
    replaceMultipleOccurrences(str4, 'x');
    printf("After:  %s\n", str4);
    
    return 0;
}