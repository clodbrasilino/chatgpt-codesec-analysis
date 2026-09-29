#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int min_swaps(const char *s1, const char *s2, size_t max_len) {
    size_t len1 = strnlen(s1, max_len);
    size_t len2 = strnlen(s2, max_len);
    
    if (len1 != len2) {
        return -1;
    }
    
    int count1_s1 = 0, count1_s2 = 0;
    size_t i;
    
    for (i = 0; i < len1; i++) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }
        if (s1[i] == '1') count1_s1++;
        if (s2[i] == '1') count1_s2++;
    }
    
    if (count1_s1 != count1_s2) {
        return -1;
    }
    
    int swaps = 0;
    int diff = 0;
    
    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                diff++;
            } else {
                diff--;
            }
            if (diff > 0) {
                swaps += diff;
            }
        }
    }
    
    return swaps;
}

int main(void) {
    char *s1 = NULL;
    char *s2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;
    ssize_t len1;
    ssize_t len2;
    
    len1 = getline(&s1, &size1, stdin);
    if (len1 == -1) {
        free(s1);
        return 1;
    }
    
    len2 = getline(&s2, &size2, stdin);
    if (len2 == -1) {
        free(s1);
        free(s2);
        return 1;
    }
    
    if (len1 > 0 && s1[len1 - 1] == '\n') {
        s1[len1 - 1] = '\0';
        len1--;
    }
    
    if (len2 > 0 && s2[len2 - 1] == '\n') {
        s2[len2 - 1] = '\0';
        len2--;
    }
    
    int result = min_swaps(s1, s2, (len1 > len2) ? len1 : len2);
    printf("%d\n", result);
    
    free(s1);
    free(s2);
    
    return 0;
}