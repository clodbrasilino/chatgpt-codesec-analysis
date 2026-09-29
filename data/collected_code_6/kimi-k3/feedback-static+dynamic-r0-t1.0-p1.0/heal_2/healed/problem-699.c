#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *s1, const char *s2, size_t len1, size_t len2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    int diff = 0;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            diff++;
        }
    }

    if (diff % 2 != 0) {
        return -1;
    }

    return diff / 2;
}

int main(void) {
    char *s1 = NULL;
    char *s2 = NULL;
    size_t cap1 = 0, cap2 = 0;
    ssize_t len1, len2;

    len1 = getline(&s1, &cap1, stdin);
    if (len1 == -1) {
        free(s1);
        return 1;
    }

    len2 = getline(&s2, &cap2, stdin);
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

    int result = min_swaps(s1, s2, (size_t)len1, (size_t)len2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    free(s1);
    free(s2);

    return 0;
}