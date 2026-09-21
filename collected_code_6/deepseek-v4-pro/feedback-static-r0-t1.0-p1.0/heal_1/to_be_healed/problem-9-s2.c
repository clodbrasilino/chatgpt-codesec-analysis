#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_rotations_same_string(const char *str) {
    if (str == NULL) return -1;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) return 0;
    
    char *doubled = (char *)malloc(2 * len + 1);
    if (doubled == NULL) return -1;
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(doubled, str);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(doubled, str);
    
    int result = -1;
    
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(doubled + i, str, len) == 0) {
            result = (int)i;
            break;
        }
    }
    
    free(doubled);
    return result;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcde";
    const char *test4 = "";
    const char *test5 = "a";
    
    printf("%d\n", min_rotations_same_string(test1));
    printf("%d\n", min_rotations_same_string(test2));
    printf("%d\n", min_rotations_same_string(test3));
    printf("%d\n", min_rotations_same_string(test4));
    printf("%d\n", min_rotations_same_string(test5));
    
    return 0;
}