#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(str2);
    
    if (len1 != len2) {
        return false;
    }
    
    if (len1 == 0) {
        return true;
    }
    
    char *copy1 = malloc(len1 + 1);
    char *copy2 = malloc(len2 + 1);
    
    if (copy1 == NULL || copy2 == NULL) {
        free(copy1);
        free(copy2);
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy1, str1);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy2, str2);
    
    qsort(copy1, len1, sizeof(char), compare_chars);
    qsort(copy2, len2, sizeof(char), compare_chars);
    
    bool result = (strcmp(copy1, copy2) == 0);
    
    free(copy1);
    free(copy2);
    
    return result;
}

int main(void) {
    const char *test1_a = "listen";
    const char *test1_b = "silent";
    printf("%s\n", are_permutations(test1_a, test1_b) ? "true" : "false");
    
    const char *test2_a = "hello";
    const char *test2_b = "world";
    printf("%s\n", are_permutations(test2_a, test2_b) ? "true" : "false");
    
    const char *test3_a = "abc";
    const char *test3_b = "abcd";
    printf("%s\n", are_permutations(test3_a, test3_b) ? "true" : "false");
    
    const char *test4_a = "";
    const char *test4_b = "";
    printf("%s\n", are_permutations(test4_a, test4_b) ? "true" : "false");
    
    const char *test5_a = NULL;
    const char *test5_b = "abc";
    /* Possible weaknesses found:
     *  Condition 'are_permutations(test5_a,test5_b)' is always false [knownConditionTrueFalse]
     *  Condition 'are_permutations(test5_a,test5_b)' is always false
     *  Calling function 'are_permutations' returns 0
     */
    printf("%s\n", are_permutations(test5_a, test5_b) ? "true" : "false");
    
    return 0;
}