#include <stdio.h>
#include <string.h>

void remove_even_chars(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t write_index = 0;
    
    for (size_t i = 1; i < size && str[i] != '\0'; i += 2) {
        str[write_index++] = str[i];
    }
    
    if (write_index < size) {
        str[write_index] = '\0';
    } else {
        str[size - 1] = '\0';
    }
}

int main(void) {
    char str1[] = "abcdefgh";
    char str2[] = "hello world";
    char str3[] = "a";
    char str4[] = "";
    
    remove_even_chars(str1, sizeof(str1));
    remove_even_chars(str2, sizeof(str2));
    remove_even_chars(str3, sizeof(str3));
    remove_even_chars(str4, sizeof(str4));
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    return 0;
}