#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = (int)strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

static void decrement_string(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = (int)strlen(str);
    int i = len - 1;
    while (i >= 0 && str[i] == '0') {
        str[i] = '9';
        i--;
    }
    if (i >= 0) {
        str[i]--;
    }
    if (str[0] == '0') {
        memmove(str, str + 1, len);
        str[len - 1] = '\0';
    }
}

char *previous_palindrome(const char *num) {
    if (num == NULL || *num == '\0') {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(num);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(result, num);
    
    decrement_string(result);
    
    while (!is_palindrome(result)) {
        decrement_string(result);
        if (result[0] == '\0') {
            free(result);
            return NULL;
        }
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "100",
        "123",
        "999",
        "1000",
        "12345",
        "9",
        "10",
        "11",
        "12321",
        "100000",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = previous_palindrome(test_cases[i]);
        if (result != NULL) {
            printf("Previous palindrome of %s is %s\n", test_cases[i], result);
            free(result);
        } else {
            printf("No previous palindrome found for %s\n", test_cases[i]);
        }
    }
    
    return 0;
}