#include <stdio.h>
#include <stdbool.h>

#define MAX_CHARS 256

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    int char_count[MAX_CHARS] = {0};
    size_t len1 = 0, len2 = 0;

    for (const char *p = str1; *p != '\0'; p++) {
        unsigned char idx = (unsigned char)*p;
        char_count[idx]++;
        len1++;
    }

    for (const char *p = str2; *p != '\0'; p++) {
        unsigned char idx = (unsigned char)*p;
        if (char_count[idx] == 0) {
            return false;
        }
        char_count[idx]--;
        len2++;
    }

    return len1 == len2;
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
     *  Condition 'are_permutations(test5_a,test5_b)' is always false [knownConditionTrueFalse]
     *  Condition 'are_permutations(test5_a,test5_b)' is always false
     */
    printf("Test 5: %s\n", are_permutations(test5_a, test5_b) ? "true" : "false");

    return 0;
}