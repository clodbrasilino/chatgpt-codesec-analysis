#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isLowercase(const char c) {
    return (c >= 'a' && c <= 'z');
}

void removeLowercaseSubstrings(char* str, size_t len) {
    if(str == NULL || len == 0) {
        return;
    }
    
    size_t i = 0;
    size_t end = len;
        
    while(i < end) {
        if(isLowercase(str[i])) {
            size_t j = i + 1;
            while(j < end && isLowercase(str[j])) {
                j++;
            }
            memmove(&str[i], &str[j], end - j + 1);
            end = end - (j - i);
        } else {
            i++;
        }
    }
}

int main() {
    char str[] = "HeLLo WOrLd";
    size_t str_len = sizeof(str) / sizeof(char) - 1;
    removeLowercaseSubstrings(str, str_len);
    printf("%s\n", str);

    return 0;
}