#include <stdio.h>
#include <string.h>
#include <limits.h>

char most_common_char(const char *str, size_t max_len) {
    if (str == NULL) {
        return '\0';
    }

    size_t count[UCHAR_MAX + 1] = {0};
    const char *ptr = str;
    
    while (*ptr != '\0' && (size_t)(ptr - str) < max_len) {
        unsigned char uc = (unsigned char)*ptr;
        count[uc]++;
        ptr++;
    }
    
    if (ptr == str) {
        return '\0';
    }

    size_t max_count = 0;
    char result = '\0';

    size_t i = 0;
    while (str[i] != '\0' && i < max_len) {
        unsigned char uc = (unsigned char)str[i];
        if (count[uc] > max_count) {
            max_count = count[uc];
            result = str[i];
        }
        i++;
    }

    return result;
}

int main(void) {
    const char *text = "improper handling of exceptional conditions";
    char res = most_common_char(text, 256);

    if (res != '\0') {
        printf("%c\n", res);
    }

    return 0;
}