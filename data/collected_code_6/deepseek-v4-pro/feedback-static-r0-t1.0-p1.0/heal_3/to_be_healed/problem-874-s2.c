#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *base) {
    if (str == NULL || base == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t base_len = strlen(base);
    
    if (base_len == 0) {
        return str_len == 0;
    }
    
    if (str_len % base_len != 0) {
        return false;
    }
    
    size_t repetitions = str_len / base_len;
    
    for (size_t i = 0; i < repetitions; i++) {
        if (strncmp(str + (i * base_len), base, base_len) != 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test_str1 = "abcabcabc";
    const char *test_base1 = "abc";
    printf("%s is concatenation of %s: %s\n", 
           test_str1, test_base1, 
           is_concatenation(test_str1, test_base1) ? "true" : "false");
    
    const char *test_str2 = "hello world";
    const char *test_base2 = "hello";
    printf("%s is concatenation of %s: %s\n", 
           test_str2, test_base2, 
           is_concatenation(test_str2, test_base2) ? "true" : "false");
    
    const char *test_str3 = "aaaaaa";
    const char *test_base3 = "aa";
    printf("%s is concatenation of %s: %s\n", 
           test_str3, test_base3, 
           is_concatenation(test_str3, test_base3) ? "true" : "false");
    
    const char *test_str4 = "";
    const char *test_base4 = "abc";
    printf("\"%s\" is concatenation of %s: %s\n", 
           test_str4, test_base4, 
           is_concatenation(test_str4, test_base4) ? "true" : "false");
    
    const char *test_str5 = "abcabcab";
    const char *test_base5 = "abc";
    printf("%s is concatenation of %s: %s\n", 
           test_str5, test_base5, 
           is_concatenation(test_str5, test_base5) ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Assignment 'test_str6=NULL', assigned value is 0
     */
    const char *test_str6 = NULL;
    const char *test_base6 = "abc";
    /* Possible weaknesses found:
     *  Condition 'test_str6==NULL' is always true
     *  Condition 'test_str6==NULL' is always true [knownConditionTrueFalse]
     */
    if (test_str6 == NULL) {
        printf("NULL is concatenation of %s: false\n", test_base6);
    } else {
        printf("NULL is concatenation of %s: %s\n", 
               test_base6, 
               is_concatenation(test_str6, test_base6) ? "true" : "false");
    }
    
    return 0;
}