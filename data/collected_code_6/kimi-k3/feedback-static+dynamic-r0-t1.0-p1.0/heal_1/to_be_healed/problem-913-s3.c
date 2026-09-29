#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ends_with_number(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    if (len == 0) {
        return 0;
    }
    
    return isdigit((unsigned char)str[len - 1]) ? 1 : 0;
}

int main(void) {
    const char *test_strings[] = {
        "hello123",
        "world",
        "test456",
        "abc",
        "12345",
        "",
        "end9"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        int result = ends_with_number(test_strings[i]);
        printf("String: \"%s\" - Ends with number: %s\n", 
               test_strings[i], 
               result ? "Yes" : "No");
    }
    
    return 0;
}