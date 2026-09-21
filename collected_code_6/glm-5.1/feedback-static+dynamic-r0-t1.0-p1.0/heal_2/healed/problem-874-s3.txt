#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, size_t str_len, const char *sub, size_t sub_len) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    if (sub_len == 0 || str_len == 0 || str_len % sub_len != 0) {
        return false;
    }

    size_t repetitions = str_len / sub_len;

    for (size_t i = 1; i < repetitions; i++) {
        if (memcmp(str, str + (i * sub_len), sub_len) != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *str1 = "abcabc";
    size_t len1 = strnlen(str1, 1024);
    const char *str2 = "abc";
    size_t len2 = strnlen(str2, 1024);
    
    if (is_concatenation(str1, len1, str2, len2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    const char *str3 = "abcabd";
    size_t len3 = strnlen(str3, 1024);
    
    if (is_concatenation(str3, len3, str2, len2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}