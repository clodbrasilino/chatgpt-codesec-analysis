#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_parenthesis_area(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    size_t i = 0;
    size_t j = 0;
    int paren_count = 0;

    while (i < len) {
        if (str[i] == '(') {
            paren_count++;
        } else if (str[i] == ')') {
            if (paren_count > 0) {
                paren_count--;
            }
        } else if (paren_count == 0) {
            result[j] = str[i];
            j++;
        }
        i++;
    }

    result[j] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);
    free(result);
}

int main(void) {
    char test_str1[] = "Hello (world) this is a (test) string.";
    char test_str2[] = "No parentheses here!";
    char test_str3[] = "(Remove) everything in (parentheses)!";
    
    remove_parenthesis_area(test_str1);
    remove_parenthesis_area(test_str2);
    remove_parenthesis_area(test_str3);

    printf("%s\n", test_str1);
    printf("%s\n", test_str2);
    printf("%s\n", test_str3);

    return 0;
}