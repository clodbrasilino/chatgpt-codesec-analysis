#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **find_substrings(const char *str, const char *sub, int *count) {
    int str_len = 0;
    int sub_len = 0;
    int capacity = 10;
    int **results = NULL;
    int idx = 0;

    if (str == NULL || sub == NULL || count == NULL) {
        return NULL;
    }

    str_len = strlen(str);
    sub_len = strlen(sub);
    
    if (sub_len == 0) {
        *count = 0;
        return NULL;
    }

    results = (int **)malloc(capacity * sizeof(int *));
    if (results == NULL) {
        return NULL;
    }

    for (int i = 0; i <= str_len - sub_len; i++) {
        if (strncmp(str + i, sub, sub_len) == 0) {
            if (idx >= capacity) {
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
            results[idx][1] = i;
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
    
    int **results = find_substrings(str, sub, &count);
    
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