#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = 0;
    for (size_t i = 0; i < 4096; i++) {
        if (str[i] == '\0') {
            len = i;
            break;
        }
    }
    
    if (len == 0) {
        return;
    }
    
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    char data1[] = "hello";
    char data2[] = "world";
    char data3[] = "example";
    char data4[] = "test";
    
    char *strings[] = {
        data1,
        data2,
        data3,
        data4,
        NULL
    };
    
    size_t count = 0;
    while (strings[count] != NULL) {
        count++;
    }
    
    reverse_strings(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}