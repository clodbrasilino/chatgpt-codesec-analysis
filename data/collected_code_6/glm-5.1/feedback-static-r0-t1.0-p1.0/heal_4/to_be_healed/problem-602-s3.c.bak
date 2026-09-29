#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_first_repeated(const char *str, char *result) {
    if (str == NULL || result == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *count = (char *)calloc(256, sizeof(char));
    if (count == NULL) {
        return -2;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            *result = str[i];
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

    char res1, res2, res3, res4;

    int ret1 = find_first_repeated(test1, &res1);
    int ret2 = find_first_repeated(test2, &res2);
    int ret3 = find_first_repeated(test3, &res3);
    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated' returns -1
     *  Assignment 'ret4=find_first_repeated(test4,&res4)', assigned value is -1
     */
    int ret4 = find_first_repeated(test4, &res4);

    if (ret1 > 0) {
        printf("Test 1: %c\n", res1);
    } else if (ret1 == 0) {
        printf("Test 1: No repeated character\n");
    } else {
        printf("Test 1: Memory allocation failed\n");
    }

    if (ret2 > 0) {
        printf("Test 2: %c\n", res2);
    } else if (ret2 == 0) {
        printf("Test 2: No repeated character\n");
    } else {
        printf("Test 2: Memory allocation failed\n");
    }

    if (ret3 > 0) {
        printf("Test 3: %c\n", res3);
    } else if (ret3 == 0) {
        printf("Test 3: No repeated character\n");
    } else {
        printf("Test 3: Memory allocation failed\n");
    }

    /* Possible weaknesses found:
     *  Condition 'ret4==-1' is always true
     *  Condition 'ret4==-1' is always true [knownConditionTrueFalse]
     */
    if (ret4 == -1) {
        printf("Test 4: Invalid input\n");
    } else if (ret4 == -2) {
        printf("Test 4: Memory allocation failed\n");
    } else {
        printf("Test 4: No repeated character\n");
    }

    return 0;
}