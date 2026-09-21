#include <stdio.h>
#include <string.h>

int isWordLengthOdd(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(word);
    
    if (length % 2 != 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    const char *testWord1 = "hello";
    const char *testWord2 = "world!";
    const char *testWord3 = NULL;
    
    int result1 = isWordLengthOdd(testWord1);
    int result2 = isWordLengthOdd(testWord2);
    int result3 = isWordLengthOdd(testWord3);
    
    printf("%d\n", result1);
    printf("%d\n", result2);
    printf("%d\n", result3);
    
    return 0;
}