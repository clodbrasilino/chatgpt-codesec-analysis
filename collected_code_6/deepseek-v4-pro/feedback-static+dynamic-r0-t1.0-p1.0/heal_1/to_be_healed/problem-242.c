#include <stdio.h>
#include <string.h>

size_t count_characters(const char *str) {
    if (str == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return strlen(str);
}

int main(void) {
    const char *test1 = "Hello, World!";
    const char *test2 = "";
    const char *test3 = NULL;
    
    printf("Test 1: %zu\n", count_characters(test1));
    printf("Test 2: %zu\n", count_characters(test2));
    printf("Test 3: %zu\n", count_characters(test3));
    
    return 0;
}