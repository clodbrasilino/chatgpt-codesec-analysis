#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubstrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int result = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++) {
        for (size_t j = i; j < length; j++) {
            if (str[i] == str[j]) {
                result++;
            }
        }
    }

    return result;
}

int main(void) {
    const char *testStr = "abcab";
    int result1 = countSubstrings(testStr);
    printf("Result 1: %d\n", result1);

    const char *testStr2 = "aba";
    int result2 = countSubstrings(testStr2);
    printf("Result 2: %d\n", result2);
    
    return 0;
}