#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    size_t write_idx = 0;
    
    for (size_t read_idx = 0; str[read_idx] != '\0'; read_idx++) {
        if (!islower((unsigned char)str[read_idx])) {
            str[write_idx++] = str[read_idx];
        }
    }
    
    str[write_idx] = '\0';
}

int main(void) {
    char test_str1[] = "Hello World!";
    char test_str2[] = "abcDEFghiJKL";
    char test_str3[] = "ALLCAPS";
    char test_str4[] = "alllower";
    
    remove_lowercase_substrings(test_str1);
    printf("%s\n", test_str1);
    
    remove_lowercase_substrings(test_str2);
    printf("%s\n", test_str2);
    
    remove_lowercase_substrings(test_str3);
    printf("%s\n", test_str3);
    
    remove_lowercase_substrings(test_str4);
    printf("%s\n", test_str4);
    
    return 0;
}