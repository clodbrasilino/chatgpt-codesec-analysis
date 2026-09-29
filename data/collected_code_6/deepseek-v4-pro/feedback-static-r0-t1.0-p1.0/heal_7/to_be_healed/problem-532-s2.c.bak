#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_CHARS 256

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return false;
    }

    int *char_count = (int*)calloc(MAX_CHARS, sizeof(int));
    if (char_count == NULL) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        char_count[(unsigned char)str1[i]]++;
        char_count[(unsigned char)str2[i]]--;
    }

    bool result = true;
    for (int i = 0; i < MAX_CHARS; i++) {
        if (char_count[i] != 0) {
            result = false;
            break;
        }
    }

    free(char_count);
    return result;
}

int main(void) {
    const char *test1_a = "listen";
    const char *test1_b = "silent";
    const char *test2_a = "hello";
    const char *test2_b = "world";
    const char *test3_a = "abc";
    const char *test3_b = "abcd";
    const char *test4_a = "aab";
    const char *test4_b = "aba";
    const char *test5_a = NULL;
    const char *test5_b = "abc";

    printf("Test 1: %s\n", are_permutations(test1_a, test1_b) ? "true" : "false");
    printf("Test 2: %s\n", are_permutations(test2_a, test2_b) ? "true" : "false");
    printf("Test 3: %s\n", are_permutations(test3_a, test3_b) ? "true" : "false");
    printf("Test 4: %s\n", are_permutations(test4_a, test4_b) ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Calling function 'are_permutations' returns 0
     *  Assignment 'test5_result=are_permutations(test5_a,test5_b)', assigned value is 0
     */
    bool test5_result = are_permutations(test5_a, test5_b);
    /* Possible weaknesses found:
     *  Condition 'test5_result' is always false
     *  Condition 'test5_result' is always false [knownConditionTrueFalse]
     */
    printf("Test 5: %s\n", test5_result ? "true" : "false");

    return 0;
}