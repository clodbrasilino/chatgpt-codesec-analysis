#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int min_rotations_same_string(const char *str) {
    if (str == NULL) return -1;
    
    size_t len = 0;
    const char *p = str;
    while (*p != '\0') {
        len++;
        p++;
        if (len > 1024 * 1024) return -1;
    }
    
    if (len == 0) return 0;
    
    if (len > SIZE_MAX / 2 - 1) return -1;
    
    size_t doubled_size = 2 * len + 1;
    char *doubled = (char *)malloc(doubled_size);
    if (doubled == NULL) return -1;
    
    if (len > 0) {
        if (doubled_size < len) {
            free(doubled);
            return -1;
        }
        memcpy(doubled, str, len);
        if (doubled_size - len < len) {
            free(doubled);
            return -1;
        }
        memcpy(doubled + len, str, len);
    }
    doubled[2 * len] = '\0';
    
    int result = -1;
    
    for (size_t i = 1; i <= len; i++) {
        if (i + len <= doubled_size) {
            if (memcmp(doubled + i, str, len) == 0) {
                result = (int)i;
                break;
            }
        }
    }
    
    free(doubled);
    return result;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcde";
    const char *test4 = "";
    const char *test5 = "a";
    
    printf("%d\n", min_rotations_same_string(test1));
    printf("%d\n", min_rotations_same_string(test2));
    printf("%d\n", min_rotations_same_string(test3));
    printf("%d\n", min_rotations_same_string(test4));
    printf("%d\n", min_rotations_same_string(test5));
    
    return 0;
}