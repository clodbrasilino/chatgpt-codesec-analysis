#include <stdio.h>
#include <stdbool.h>

#define MAX_CHARS 256

bool are_permutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    int char_count[MAX_CHARS] = {0};
    int total_count = 0;

    for (const char *p = str1; *p != '\0'; p++) {
        unsigned char idx = (unsigned char)*p;
        char_count[idx]++;
        total_count++;
    }

    for (const char *p = str2; *p != '\0'; p++) {
        unsigned char idx = (unsigned char)*p;
        char_count[idx]--;
        total_count--;
        if (char_count[idx] < 0) {
            return false;
        }
    }

    if (total_count != 0) {
        return false;
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

    bool result1 = are_permutations(test1_a, test1_b);
    bool result2 = are_permutations(test2_a, test2_b);
    bool result3 = are_permutations(test3_a, test3_b);
    bool result4 = are_permutations(test4_a, test4_b);
    bool result5 = are_permutations(test5_a, test5_b);

    printf("Test 1: %s\n", result1 ? "true" : "false");
    printf("Test 2: %s\n", result2 ? "true" : "false");
    printf("Test 3: %s\n", result3 ? "true" : "false");
    printf("Test 4: %s\n", result4 ? "true" : "false");
    printf("Test 5: %s\n", result5 ? "true" : "false");

    return 0;
}