#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strlen(const char *str) {
    if (str == NULL) return 0;
    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    return len;
}

char *longest_common_prefix(char **strs, int strs_len) {
    if (strs_len <= 0 || strs == NULL) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) return NULL;
        empty[0] = '\0';
        return empty;
    }

    for (int i = 0; i < strs_len; i++) {
        if (strs[i] == NULL) {
            char *empty = (char *)malloc(1);
            if (empty == NULL) return NULL;
            empty[0] = '\0';
            return empty;
        }
    }

    size_t min_len = safe_strlen(strs[0]);
    for (int i = 1; i < strs_len; i++) {
        size_t current_len = safe_strlen(strs[i]);
        if (current_len < min_len) {
            min_len = current_len;
        }
    }

    char *prefix = (char *)malloc(min_len + 1);
    if (prefix == NULL) return NULL;

    size_t prefix_len = 0;
    for (size_t i = 0; i < min_len; i++) {
        char current_char = strs[0][i];
        int mismatch = 0;
        for (int j = 1; j < strs_len; j++) {
            size_t str_len = safe_strlen(strs[j]);
            if (i >= str_len || strs[j][i] != current_char) {
                mismatch = 1;
                break;
            }
        }
        if (mismatch) {
            break;
        }
        if (prefix_len < min_len) {
            prefix[prefix_len++] = current_char;
        }
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