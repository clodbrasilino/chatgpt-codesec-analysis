#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return -1;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return -1;
    }

    unsigned char *count = (unsigned char *)calloc(256, sizeof(unsigned char));
    if (count == NULL) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            free(count);
            return c;
        }
        count[c]++;
    }

    free(count);
    return -1;
}

int main(void) {
    const char test1[] = "abcdefa";
    const char test2[] = "abcdef";
    const char test3[] = "";
    /* Possible weaknesses found:
     *  Assignment 'test4=NULL', assigned value is 0
     */
    const char *test4 = NULL;
    size_t test4_len = 0;

    /* Possible weaknesses found:
     *  Condition 'test4' is always false
     *  Condition 'test4' is always false [knownConditionTrueFalse]
     */
    test4_len = test4 ? strnlen(test4, 0) : 0;

    int res1 = find_first_repeated(test1, sizeof(test1) - 1);
    int res2 = find_first_repeated(test2, sizeof(test2) - 1);
    int res3 = find_first_repeated(test3, sizeof(test3) - 1);
    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated' returns -1
     *  Assignment 'res4=find_first_repeated(test4,test4_len)', assigned value is -1
     */
    int res4 = find_first_repeated(test4, test4_len);

    if (res1 != -1) {
        printf("Test 1: %c\n", res1);
    } else {
        printf("Test 1: No repeated character\n");
    }

    if (res2 != -1) {
        printf("Test 2: %c\n", res2);
    } else {
        printf("Test 2: No repeated character\n");
    }

    if (res3 != -1) {
        printf("Test 3: %c\n", res3);
    } else {
        printf("Test 3: No repeated character\n");
    }

    /* Possible weaknesses found:
     *  Condition 'res4!=-1' is always false
     *  Condition 'res4!=-1' is always false [knownConditionTrueFalse]
     */
    if (res4 != -1) {
        printf("Test 4: %c\n", res4);
    } else {
        printf("Test 4: No repeated character\n");
    }

    return 0;
}