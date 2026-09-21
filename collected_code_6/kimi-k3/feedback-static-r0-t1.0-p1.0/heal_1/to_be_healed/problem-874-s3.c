#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t substr_len = strlen(substr);
    
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
    
    printf("%s\n", is_concatenation(test1, test2) ? "true" : "false");
    printf("%s\n", is_concatenation(test3, test2) ? "true" : "false");
    printf("%s\n", is_concatenation(test4, test5) ? "true" : "false");
    
    return 0;
}