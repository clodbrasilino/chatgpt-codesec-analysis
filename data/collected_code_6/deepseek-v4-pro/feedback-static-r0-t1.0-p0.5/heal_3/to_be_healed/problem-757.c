#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *reverse_string(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }
    
    char *reversed = (char *)malloc(len + 1);
    if (reversed == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

int count_reverse_pairs(char **strs, int n) {
    if (strs == NULL || n <= 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (strs[i] == NULL) {
            return 0;
        }
    }

    size_t *lens = (size_t *)malloc(n * sizeof(size_t));
    if (lens == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        lens[i] = strlen(strs[i]);
    }

    char **reversed_strs = (char **)malloc(n * sizeof(char *));
    if (reversed_strs == NULL) {
        free(lens);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        reversed_strs[i] = reverse_string(strs[i], lens[i]);
        if (reversed_strs[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(reversed_strs[j]);
            }
            free(reversed_strs);
            free(lens);
            return 0;
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (lens[i] == lens[j]) {
                if (strcmp(strs[i], reversed_strs[j]) == 0) {
                    count++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(reversed_strs[i]);
    }
    free(reversed_strs);
    free(lens);

    return count;
}

int main(void) {
    char *strs[] = {"abc", "cba", "def", "fed", "xyz"};
    int n = sizeof(strs) / sizeof(strs[0]);
    int result = count_reverse_pairs(strs, n);
    printf("%d\n", result);
    return 0;
}