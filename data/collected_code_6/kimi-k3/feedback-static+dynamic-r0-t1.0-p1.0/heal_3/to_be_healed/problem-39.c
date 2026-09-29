#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool canRearrange(const char *str, size_t maxlen) {
    if (str == NULL) {
        return false;
    }

    size_t len = 0;
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    if (len == maxlen && str[len] != '\0') {
        return false;
    }

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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        printf("String: %s -> %s\n", tests[i], canRearrange(tests[i], strlen(tests[i]) + 1) ? "true" : "false");
    }

    return 0;
}