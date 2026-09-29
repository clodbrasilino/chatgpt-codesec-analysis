#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_lowercase_substrings(char *str) {
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

    size_t res_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (islower((unsigned char)str[i])) {
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
        } else {
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);
    free(result);
}

int main(void) {
    char test_str1[] = "Hello world! THIS is A test.";
    char test_str2[] = "ALLCAPS";
    char test_str3[] = "alllower";
    char test_str4[] = "MixedCASE123";

    remove_lowercase_substrings(test_str1);
    printf("%s\n", test_str1);

    remove_lowercase_substrings(test_str2);
    printf("%s\n", test_str2);

    remove_lowercase_substrings(test_str3);
    printf("%s\n", test_str3);

    remove_lowercase_substrings(test_str4);
    printf("%s\n", test_str4);

    return 0;
}