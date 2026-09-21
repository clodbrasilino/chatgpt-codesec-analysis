#include <stdio.h>
#include <ctype.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    size_t write_idx = 0;
    size_t read_idx = 0;

    while (str[read_idx] != '\0') {
        if (islower((unsigned char)str[read_idx])) {
            while (str[read_idx] != '\0' && islower((unsigned char)str[read_idx])) {
                read_idx++;
            }
        } else {
            str[write_idx++] = str[read_idx++];
        }
    }
    str[write_idx] = '\0';
}

int main(void) {
    char str1[] = "Hello World!";
    char str2[] = "abc DEF ghi JKL";
    char str3[] = "ALLCAPS";
    char str4[] = "alllower";
    
    remove_lowercase_substrings(str1);
    remove_lowercase_substrings(str2);
    remove_lowercase_substrings(str3);
    remove_lowercase_substrings(str4);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    return 0;
}