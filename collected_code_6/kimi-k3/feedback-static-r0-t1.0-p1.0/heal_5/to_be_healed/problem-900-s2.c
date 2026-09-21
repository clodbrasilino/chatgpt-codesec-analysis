#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[12];
    int len = snprintf(num_str, sizeof(num_str), "%d", num);
    
    if (len < 0 || (size_t)len >= sizeof(num_str)) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    if (str_len < (size_t)len) {
        return false;
    }
    
    return strncmp(str, num_str, (size_t)len) == 0;
}

int main(void) {
    const char *str = "123Hello";
    int num = 123;

    if (starts_with_number(str, num)) {
        printf("The string starts with %d\n", num);
    } else {
        printf("The string does not start with %d\n", num);
    }

    return 0;
}