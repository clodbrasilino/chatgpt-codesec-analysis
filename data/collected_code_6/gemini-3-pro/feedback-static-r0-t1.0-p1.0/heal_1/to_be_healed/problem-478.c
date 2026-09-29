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
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        return;
    }

    size_t temp_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (islower((unsigned char)str[i])) {
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
        } else {
            temp[temp_idx++] = str[i++];
        }
    }
    
    temp[temp_idx] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, temp);
    free(temp);
}

int main() {
    char str1[] = "Hello World!";
    char str2[] = "abc DEF ghi JKL";
    char str3[] = "ALLCAPS";
    char str4[] = "alllower";
    
    remove_lowercase_substrings(str1);
    remove_lowercase_substrings(str2);
    remove_lowercase_substrings(str3);
    remove_lowercase_substrings(str4);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    return 0;
}