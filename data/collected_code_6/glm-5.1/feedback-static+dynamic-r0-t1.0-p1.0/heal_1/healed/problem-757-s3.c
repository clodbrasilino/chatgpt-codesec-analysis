#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse_string(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }
    char *rev = (char *)malloc(len + 1);
    if (rev == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        rev[i] = str[len - 1 - i];
    }
    rev[len] = '\0';
    return rev;
}

int count_reverse_pairs(char **strings, int count, size_t *lengths) {
    if (strings == NULL || lengths == NULL || count <= 0) {
        return 0;
    }
    int pair_count = 0;
    for (int i = 0; i < count; i++) {
        if (strings[i] != NULL && lengths[i] > 0) {
            char *rev = reverse_string(strings[i], lengths[i]);
            if (rev != NULL) {
                for (int j = i + 1; j < count; j++) {
                    if (strings[j] != NULL && lengths[j] > 0 && lengths[i] == lengths[j] && strcmp(strings[i], strings[j]) != 0 && strcmp(rev, strings[j]) == 0) {
                        pair_count++;
                    }
                }
                free(rev);
            }
        }
    }
    return pair_count;
}

int main(void) {
    char *arr[] = {"abc", "cba", "hello", "world", "olleh", "abc", "cba"};
    int count = sizeof(arr) / sizeof(arr[0]);
    size_t lengths[] = {3, 3, 5, 5, 5, 3, 3};
    int result = count_reverse_pairs(arr, count, lengths);
    printf("%d\n", result);
    return 0;
}