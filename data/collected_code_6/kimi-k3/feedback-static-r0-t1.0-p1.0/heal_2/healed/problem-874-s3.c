#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, size_t str_len, const char *substr, size_t substr_len) {
    if (str == NULL || substr == NULL) {
        return false;
    }
    
    if (substr_len == 0) {
        return false;
    }
    
    if (str_len == 0 || str_len % substr_len != 0) {
        return false;
    }
    
    for (size_t i = 0; i < str_len; i += substr_len) {
        if (strncmp(str + i, substr, substr_len) != 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test1 = "abcabcabc";
    const char *test2 = "abc";
    const char *test3 = "abcdabc";
    const char *test4 = "xyzxyz";
    const char *test5 = "xyz";
    
    printf("%s\n", is_concatenation(test1, sizeof("abcabcabc") - 1, test2, sizeof("abc") - 1) ? "true" : "false");
    printf("%s\n", is_concatenation(test3, sizeof("abcdabc") - 1, test2, sizeof("abc") - 1) ? "true" : "false");
    printf("%s\n", is_concatenation(test4, sizeof("xyzxyz") - 1, test5, sizeof("xyz") - 1) ? "true" : "false");
    
    return 0;
}