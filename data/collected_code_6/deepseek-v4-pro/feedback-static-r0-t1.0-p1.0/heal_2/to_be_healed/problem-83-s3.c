#include <stdio.h>
#include <string.h>

char string_sum(const char *str) {
    char sum = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i;
    
    for (i = 0; i < len; i++) {
        sum += str[i];
    }
    
    return sum;
}

int main(void) {
    const char *test = "Hello";
    char result = string_sum(test);
    
    printf("String: %s\n", test);
    printf("Character sum: %d\n", result);
    
    return 0;
}