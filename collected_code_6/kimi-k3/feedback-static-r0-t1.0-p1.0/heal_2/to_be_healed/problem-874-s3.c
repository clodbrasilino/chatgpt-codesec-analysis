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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s\n", is_concatenation(test1, strlen(test1), test2, strlen(test2)) ? "true" : "false");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s\n", is_concatenation(test3, strlen(test3), test2, strlen(test2)) ? "true" : "false");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s\n", is_concatenation(test4, strlen(test4), test5, strlen(test5)) ? "true" : "false");
    
    return 0;
}