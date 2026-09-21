#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str, size_t n) {
    size_t count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (count >= n) {
            break;
        }
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
    }
}

int main(void) {
    char str[] = "This is a test, with spaces, and dots...";
    size_t n = 3;
    
    printf("Original: %s\n", str);
    replace_chars(str, n);
    printf("Modified: %s\n", str);
    
    return 0;
}