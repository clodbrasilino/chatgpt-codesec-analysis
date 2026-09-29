#include <stdio.h>
#include <string.h>

int total_ascii_value(const char *str, size_t max_len) {
    int total = 0;
    size_t str_len = strnlen(str, max_len);
    
    for (size_t i = 0; i < str_len; i++) {
        total += (unsigned char)str[i];
    }
    
    return total;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'test_string="Hello, World!"', assigned value is "Hello, World!"
     */
    const char *test_string = "Hello, World!";
    size_t max_len = 100;
    
    /* Possible weaknesses found:
     *  Condition 'strlen(test_string)<max_len' is always true
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Condition 'strlen(test_string)<max_len' is always true [knownConditionTrueFalse]
     */
    if (strlen(test_string) < max_len) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        max_len = strlen(test_string);
    }
    
    int result = total_ascii_value(test_string, max_len);
    
    printf("Total ASCII value of \"%s\": %d\n", test_string, result);
    
    return 0;
}