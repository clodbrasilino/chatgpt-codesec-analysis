#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool canRearrange(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return true;
    }
    
    int freq[26] = {0};
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            freq[str[i] - 'a']++;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            freq[str[i] - 'A']++;
        }
    }
    
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }
    
    return maxFreq <= (int)((len + 1) / 2);
}

int main(void) {
    const char *tests[] = {
        "aab",
        "aaab",
        "abc",
        "aabb",
        "aaabb",
        "aabbc",
        "abcd",
        "aabbcc",
        "aaabbb",
        NULL
    };
    
    for (int i = 0; tests[i] != NULL; i++) {
        printf("String: %s -> %s\n", tests[i], canRearrange(tests[i]) ? "true" : "false");
    }
    
    return 0;
}