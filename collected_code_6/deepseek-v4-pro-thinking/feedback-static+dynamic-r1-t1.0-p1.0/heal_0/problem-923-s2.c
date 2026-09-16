#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t shortestCommonSupersequenceLength(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return (size_t)-1;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    const char *s1 = str1;
    const char *s2 = str2;

    if (len1 < len2) {
        size_t tempLen = len1;
        len1 = len2;
        len2 = tempLen;

        const char *tempStr = s1;
        s1 = s2;
        s2 = tempStr;
    }

    size_t *prev = calloc(len2 + 1, sizeof(size_t));
    if (prev == NULL) {
        return (size_t)-1;
    }

    size_t *curr = calloc(len2 + 1, sizeof(size_t));
    if (curr == NULL) {
        free(prev);
        return (size_t)-1;
    }

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = prev[j] > curr[j - 1] ? prev[j] : curr[j - 1];
            }
        }

        size_t *temp = prev;
        prev = curr;
        curr = temp;
    }

    size_t lcs = prev[len2];

    free(prev);
    free(curr);

    return len1 + len2 - lcs;
}

int main(void) {
    const char *str1 = "AGGTAB";
    const char *str2 = "GXTXAYB";

    size_t result = shortestCommonSupersequenceLength(str1, str2);

    if (result == (size_t)-1) {
        printf("Error\n");
        return 1;
    }

    printf("%zu\n", result);

    return 0;
}