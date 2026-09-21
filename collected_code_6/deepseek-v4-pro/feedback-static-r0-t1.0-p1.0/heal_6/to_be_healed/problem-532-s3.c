#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static int compare_chars(const void *a, const void *b) {
    return (*(const unsigned char *)a - *(const unsigned char *)b);
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
    
    size_t size = len1;
    char *copy1 = malloc(size);
    char *copy2 = malloc(size);
    
    if (copy1 == NULL || copy2 == NULL) {
        free(copy1);
        free(copy2);
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy1, str1, size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy2, str2, size);
    
    qsort(copy1, size, sizeof(char), compare_chars);
    qsort(copy2, size, sizeof(char), compare_chars);
    
    bool result = (memcmp(copy1, copy2, size) == 0);
    
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
     *  Assignment 'result=are_permutations(test5_a,test5_b)', assigned value is 0
     *  Calling function 'are_permutations' returns 0
     */
    bool result = are_permutations(test5_a, test5_b);
    /* Possible weaknesses found:
     *  Condition 'result' is always false
     *  Condition 'result' is always false [knownConditionTrueFalse]
     */
    printf("%s\n", result ? "true" : "false");
    
    return 0;
}