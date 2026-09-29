#include <stdio.h>
#include <string.h>

int total_ascii_value(const char *str) {
    int total = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    
    for (size_t i = 0; i < length; i++) {
        total += (unsigned char)str[i];
    }
    
    return total;
}

int main(void) {
    const char *test_string = "Hello, World!";
    int result = total_ascii_value(test_string);
    
    printf("Total ASCII value of \"%s\": %d\n", test_string, result);
    
    return 0;
}