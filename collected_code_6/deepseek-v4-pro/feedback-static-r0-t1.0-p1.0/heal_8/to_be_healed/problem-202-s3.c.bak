#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *remove_even_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    size_t new_len = (len + 1) / 2;
    
    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "abcdefgh",
        "a",
        "",
        "abc",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = remove_even_chars(test_cases[i]);
        if (result != NULL) {
            printf("Input: \"%s\" -> Output: \"%s\"\n", test_cases[i], result);
            free(result);
        }
    }
    
    /* Possible weaknesses found:
     *  Calling function 'remove_even_chars' returns 0
     *  Assignment 'null_result=remove_even_chars(NULL)', assigned value is 0
     */
    char *null_result = remove_even_chars(NULL);
    
    /* Possible weaknesses found:
     *  Condition 'null_result==NULL' is always true
     *  Condition 'null_result==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_result == NULL) {
        printf("NULL input -> NULL output\n");
    } else {
        free(null_result);
    }
    
    return 0;
}