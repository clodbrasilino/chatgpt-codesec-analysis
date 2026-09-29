#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest_common_prefix(char **strs, int strs_len) {
    if (strs_len == 0 || strs == NULL) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) return NULL;
        empty[0] = '\0';
        return empty;
    }

    int min_len = strlen(strs[0]);
    for (int i = 1; i < strs_len; i++) {
        int current_len = strlen(strs[i]);
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    char *prefix = (char *)malloc(min_len + 1);
    if (prefix == NULL) return NULL;

    int prefix_len = 0;
    for (int i = 0; i < min_len; i++) {
        char current_char = strs[0][i];
        int mismatch = 0;
        for (int j = 1; j < strs_len; j++) {
            if (strs[j][i] != current_char) {
                mismatch = 1;
                break;
            }
        }
        if (mismatch) {
            break;
        }
        prefix[prefix_len++] = current_char;
    }

    prefix[prefix_len] = '\0';
    return prefix;
}

int main(void) {
    char *test1[] = {"flower", "flow", "flight"};
    char *result1 = longest_common_prefix(test1, 3);
    if (result1 != NULL) {
        printf("Test 1: %s\n", result1);
        free(result1);
    }

    char *test2[] = {"dog", "racecar", "car"};
    char *result2 = longest_common_prefix(test2, 3);
    if (result2 != NULL) {
        printf("Test 2: %s\n", result2);
        free(result2);
    }

    char *test3[] = {"interspecies", "interstellar", "interstate"};
    char *result3 = longest_common_prefix(test3, 3);
    if (result3 != NULL) {
        printf("Test 3: %s\n", result3);
        free(result3);
    }

    char *test4[] = {""};
    char *result4 = longest_common_prefix(test4, 1);
    if (result4 != NULL) {
        printf("Test 4: %s\n", result4);
        free(result4);
    }

    char *result5 = longest_common_prefix(NULL, 0);
    if (result5 != NULL) {
        printf("Test 5: %s\n", result5);
        free(result5);
    }

    return 0;
}