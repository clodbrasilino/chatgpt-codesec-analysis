#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    if (str == NULL) return;
    
    int write_idx = 0;
    int read_idx = 0;
    size_t len = strlen(str);
    
    for (read_idx = 0; read_idx < (int)len; read_idx++) {
        if (read_idx % 2 == 0) {
            str[write_idx++] = str[read_idx];
        }
    }
    str[write_idx] = '\0';
}

int main(void) {
    char str1[] = "abcdefgh";
    char str2[] = "123456789";
    char str3[] = "a";
    char str4[] = "";
    char str5[] = "Hello, World!";
    
    remove_odd_chars(str1);
    remove_odd_chars(str2);
    remove_odd_chars(str3);
    remove_odd_chars(str4);
    remove_odd_chars(str5);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    printf("%s\n", str5);
    
    return 0;
}