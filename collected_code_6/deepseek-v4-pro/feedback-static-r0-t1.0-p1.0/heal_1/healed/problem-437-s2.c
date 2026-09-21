#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str, size_t size) {
    size_t i, j = 0;
    
    if (str == NULL || size == 0) {
        return;
    }
    
    for (i = 0; i < size && str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str1[] = "abcdefgh";
    char str2[] = "hello world";
    char str3[] = "a";
    char str4[] = "";
    
    printf("Original: %s\n", str1);
    remove_odd_chars(str1, sizeof(str1));
    printf("Modified: %s\n\n", str1);
    
    printf("Original: %s\n", str2);
    remove_odd_chars(str2, sizeof(str2));
    printf("Modified: %s\n\n", str2);
    
    printf("Original: %s\n", str3);
    remove_odd_chars(str3, sizeof(str3));
    printf("Modified: %s\n\n", str3);
    
    printf("Original: %s\n", str4);
    remove_odd_chars(str4, sizeof(str4));
    printf("Modified: %s\n", str4);
    
    return 0;
}