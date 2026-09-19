#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_first_repeated(const char *str, char *out) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *count = (char *)calloc(256, sizeof(char));
    if (count == NULL) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            *out = str[i];
            free(count);
            return 1;
        }
        count[c]++;
    }

    free(count);
    return 0;
}

int main(void) {
    const char *test1 = "abcdefa";
    const char *test2 = "abcdef";
    const char *test3 = "";
    const char *test4 = NULL;

    char res;
    int ret;

    ret = find_first_repeated(test1, &res);
    if (ret == 1) {
        printf("Test 1: %c\n", res);
    } else if (ret == 0) {
        printf("Test 1: No repeated character\n");
    } else {
        printf("Test 1: Memory allocation failed\n");
    }

    ret = find_first_repeated(test2, &res);
    if (ret == 1) {
        printf("Test 2: %c\n", res);
    } else if (ret == 0) {
        printf("Test 2: No repeated character\n");
    } else {
        printf("Test 2: Memory allocation failed\n");
    }

    ret = find_first_repeated(test3, &res);
    if (ret == 1) {
        printf("Test 3: %c\n", res);
    } else if (ret == 0) {
        printf("Test 3: No repeated character\n");
    } else {
        printf("Test 3: Memory allocation failed\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated' returns 0
     *  Assignment 'ret=find_first_repeated(test4,&res)', assigned value is 0
     */
    ret = find_first_repeated(test4, &res);
    /* Possible weaknesses found:
     *  Condition 'ret==1' is always false
     *  Condition 'ret==1' is always false [knownConditionTrueFalse]
     */
    if (ret == 1) {
        printf("Test 4: %c\n", res);
    /* Possible weaknesses found:
     *  Condition 'ret==0' is always true
     *  Condition 'ret==0' is always true [knownConditionTrueFalse]
     */
    } else if (ret == 0) {
        printf("Test 4: No repeated character\n");
    } else {
        printf("Test 4: Memory allocation failed\n");
    }

    return 0;
}