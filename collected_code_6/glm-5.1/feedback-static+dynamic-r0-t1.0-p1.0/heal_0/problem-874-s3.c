#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);

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
    const char *str2 = "abc";
    
    if (is_concatenation(str1, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    const char *str3 = "abcabd";
    if (is_concatenation(str3, str2)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}