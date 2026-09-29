#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return 0;
    }
    
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[32];
    int ret = snprintf(num_str, sizeof(num_str), "%d", num);
    if (ret < 0 || ret >= (int)sizeof(num_str)) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t num_len = strlen(num_str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(str) < num_len) {
        return 0;
    }
    
    return (strncmp(str, num_str, num_len) == 0);
}

int main(void) {
    const char *test1 = "123hello";
    const char *test2 = "456world";
    const char *test3 = "  789test";
    const char *test4 = "no_number";
    
    printf("Test 1: %s\n", starts_with_number(test1, 123) ? "true" : "false");
    printf("Test 2: %s\n", starts_with_number(test2, 123) ? "true" : "false");
    printf("Test 3: %s\n", starts_with_number(test3, 789) ? "true" : "false");
    printf("Test 4: %s\n", starts_with_number(test4, 999) ? "true" : "false");
    
    return 0;
}