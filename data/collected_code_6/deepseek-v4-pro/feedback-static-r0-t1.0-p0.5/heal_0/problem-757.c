#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *reverse_string(const char *str) {
    size_t len = strlen(str);
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

    int count = 0;
    char **reversed_strs = (char **)malloc(n * sizeof(char *));
    if (reversed_strs == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        reversed_strs[i] = reverse_string(strs[i]);
        if (reversed_strs[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(reversed_strs[j]);
            }
            free(reversed_strs);
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(strs[i], reversed_strs[j]) == 0) {
                count++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(reversed_strs[i]);
    }
    free(reversed_strs);

    return count;
}

int main(void) {
    char *strs[] = {"abc", "cba", "def", "fed", "xyz"};
    int n = sizeof(strs) / sizeof(strs[0]);
    int result = count_reverse_pairs(strs, n);
    printf("%d\n", result);
    return 0;
}