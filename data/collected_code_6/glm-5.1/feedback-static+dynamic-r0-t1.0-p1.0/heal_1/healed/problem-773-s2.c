#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **find_substrings(const char *str, size_t str_len, const char *sub, size_t sub_len, int *count) {
    size_t capacity = 10;
    int **results = NULL;
    int idx = 0;

    if (str == NULL || sub == NULL || count == NULL) {
        return NULL;
    }

    if (sub_len == 0) {
        *count = 0;
        return NULL;
    }

    results = (int **)malloc(capacity * sizeof(int *));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= str_len - sub_len; i++) {
        if (memcmp(str + i, sub, sub_len) == 0) {
            if ((size_t)idx >= capacity) {
                capacity *= 2;
                int **temp = (int **)realloc(results, capacity * sizeof(int *));
                if (temp == NULL) {
                    for (int j = 0; j < idx; j++) {
                        free(results[j]);
                    }
                    free(results);
                    return NULL;
                }
                results = temp;
            }
            results[idx] = (int *)malloc(2 * sizeof(int));
            if (results[idx] == NULL) {
                for (int j = 0; j < idx; j++) {
                    free(results[j]);
                }
                free(results);
                return NULL;
            }
            results[idx][0] = idx + 1;
            results[idx][1] = (int)i;
            idx++;
            i += sub_len - 1;
        }
    }

    *count = idx;
    return results;
}

int main(int argc, char *argv[]) {
    const char *str = "abababaabab";
    const char *sub = "aba";
    int count = 0;
    
    size_t str_len = strnlen(str, 256);
    size_t sub_len = strnlen(sub, 256);
    
    int **results = find_substrings(str, str_len, sub, sub_len, &count);
    
    if (results != NULL) {
        for (int i = 0; i < count; i++) {
            printf("Occurrence: %d, Position: %d\n", results[i][0], results[i][1]);
            free(results[i]);
        }
        free(results);
    } else {
        printf("No occurrences found or memory allocation failed.\n");
    }
    
    return 0;
}