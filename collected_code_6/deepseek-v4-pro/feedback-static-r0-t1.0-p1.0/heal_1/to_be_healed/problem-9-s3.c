#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_rotations_same_string(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    char *doubled = (char *)malloc(2 * len + 1);
    if (doubled == NULL) {
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(doubled, str);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(doubled, str);
    
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(str, doubled + i, len) == 0) {
            free(doubled);
            return (int)i;
        }
    }
    
    free(doubled);
    return (int)len;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcab";
    const char *test4 = "abc";
    const char *test5 = "";
    
    printf("%d\n", min_rotations_same_string(test1));
    printf("%d\n", min_rotations_same_string(test2));
    printf("%d\n", min_rotations_same_string(test3));
    printf("%d\n", min_rotations_same_string(test4));
    printf("%d\n", min_rotations_same_string(test5));
    
    return 0;
}