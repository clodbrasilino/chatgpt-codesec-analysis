#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *minimize_string(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    int freq[256] = {0};
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    char target = str[0];
    int max_freq = freq[(unsigned char)str[0]];
    for (int i = 1; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            target = (char)i;
        }
    }

    if (max_freq == (int)len) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t new_len = len - max_freq;
    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != target) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test1 = "aabbbcc";
    const char *test2 = "aaaa";
    const char *test3 = "abc";
    const char *test4 = "";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;

    char *r1 = minimize_string(test1);
    char *r2 = minimize_string(test2);
    char *r3 = minimize_string(test3);
    char *r4 = minimize_string(test4);
    /* Possible weaknesses found:
     *  Assignment 'r5=minimize_string(test5)', assigned value is 0
     *  Calling function 'minimize_string' returns 0
     */
    char *r5 = minimize_string(test5);

    printf("Input: %s, Output: %s\n", test1 ? test1 : "NULL", r1 ? r1 : "NULL");
    printf("Input: %s, Output: %s\n", test2 ? test2 : "NULL", r2 ? r2 : "NULL");
    printf("Input: %s, Output: %s\n", test3 ? test3 : "NULL", r3 ? r3 : "NULL");
    printf("Input: %s, Output: %s\n", test4 ? test4 : "NULL", r4 ? r4 : "NULL");
    /* Possible weaknesses found:
     *  Condition 'r5' is always false [knownConditionTrueFalse]
     *  Condition 'test5' is always false [knownConditionTrueFalse]
     *  Condition 'test5' is always false
     *  Condition 'r5' is always false
     */
    printf("Input: %s, Output: %s\n", test5 ? test5 : "NULL", r5 ? r5 : "NULL");

    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);

    return 0;
}