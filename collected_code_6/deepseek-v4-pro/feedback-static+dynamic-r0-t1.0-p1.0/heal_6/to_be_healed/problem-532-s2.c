#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_CHARS 256

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    int char_count[MAX_CHARS] = {0};
    size_t i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        char_count[(unsigned char)str1[i]]++;
        char_count[(unsigned char)str2[i]]--;
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return false;
    }

    for (int j = 0; j < MAX_CHARS; j++) {
        if (char_count[j] != 0) {
            return false;
        }
    }

    return true;
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
     *  Assignment 'result5=are_permutations(test5_a,test5_b)', assigned value is 0
     *  Calling function 'are_permutations' returns 0
     */
    bool result5 = are_permutations(test5_a, test5_b);
    /* Possible weaknesses found:
     *  Condition 'result5' is always false [knownConditionTrueFalse]
     *  Condition 'result5' is always false
     */
    printf("Test 5: %s\n", result5 ? "true" : "false");

    return 0;
}