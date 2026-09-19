#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool check_password(const char *str, size_t min_len, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    if (len < min_len || len > max_len) {
        return false;
    }
    
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            has_upper = true;
        } else if (islower((unsigned char)str[i])) {
            has_lower = true;
        } else if (isdigit((unsigned char)str[i])) {
            has_digit = true;
        }
        
        if (has_upper && has_lower && has_digit) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    const char *test1 = "Password123";
    const char *test2 = "password";
    const char *test3 = "PASSWORD123";
    const char *test4 = "Pass123";
    const char *test5 = NULL;
    
    printf("Test 1: %s\n", check_password(test1, 8, 20) ? "valid" : "invalid");
    printf("Test 2: %s\n", check_password(test2, 8, 20) ? "valid" : "invalid");
    printf("Test 3: %s\n", check_password(test3, 8, 20) ? "valid" : "invalid");
    printf("Test 4: %s\n", check_password(test4, 8, 20) ? "valid" : "invalid");
    
    /* Possible weaknesses found:
     *  Condition 'check_password(test5,8,20)' is always false [knownConditionTrueFalse]
     *  Condition 'check_password(test5,8,20)' is always false
     *  Calling function 'check_password' returns 0
     */
    printf("Test 5: %s\n", check_password(test5, 8, 20) ? "valid" : "invalid");
    
    return 0;
}