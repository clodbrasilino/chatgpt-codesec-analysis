#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_reverse(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return false;
    }
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if (len1 != len2) {
        return false;
    }
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[len1 - 1 - i]) {
            return false;
        }
    }
    return true;
}

size_t count_reverse_pairs(const char **strings, size_t count) {
    if (strings == NULL) {
        return 0;
    }
    size_t pairs = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        for (size_t j = i + 1; j < count; j++) {
            if (strings[j] == NULL) {
                continue;
            }
            if (is_reverse(strings[i], strings[j])) {
                pairs++;
            }
        }
    }
    return pairs;
}

int main(void) {
    const char **list = malloc(8 * sizeof(const char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    
    list[0] = "abc";
    list[1] = "cba";
    list[2] = "hello";
    list[3] = "world";
    list[4] = "olleh";
    list[5] = "xyz";
    list[6] = "zyx";
    list[7] = "abc";
    
    size_t count = 8;
    size_t result = count_reverse_pairs(list, count);
    
    printf("%zu\n", result);
    
    free(list);
    
    return EXIT_SUCCESS;
}