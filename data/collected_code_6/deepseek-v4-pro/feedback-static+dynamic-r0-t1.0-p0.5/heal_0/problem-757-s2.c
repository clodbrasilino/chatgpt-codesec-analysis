#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_reverse_pairs(char **strs, int n) {
    int count = 0;
    char **seen = (char **)malloc(n * sizeof(char *));
    int *seen_len = (int *)malloc(n * sizeof(int));
    int seen_count = 0;

    if (seen == NULL || seen_len == NULL) {
        free(seen);
        free(seen_len);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        int len = strlen(strs[i]);
        char *rev = (char *)malloc((len + 1) * sizeof(char));
        if (rev == NULL) {
            for (int j = 0; j < seen_count; j++) {
                free(seen[j]);
            }
            free(seen);
            free(seen_len);
            return -1;
        }

        for (int j = 0; j < len; j++) {
            rev[j] = strs[i][len - 1 - j];
        }
        rev[len] = '\0';

        int found = 0;
        for (int j = 0; j < seen_count; j++) {
            if (seen_len[j] == len && strcmp(seen[j], rev) == 0) {
                count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            seen[seen_count] = (char *)malloc((len + 1) * sizeof(char));
            if (seen[seen_count] == NULL) {
                free(rev);
                for (int j = 0; j < seen_count; j++) {
                    free(seen[j]);
                }
                free(seen);
                free(seen_len);
                return -1;
            }
            strcpy(seen[seen_count], strs[i]);
            seen_len[seen_count] = len;
            seen_count++;
        }

        free(rev);
    }

    for (int j = 0; j < seen_count; j++) {
        free(seen[j]);
    }
    free(seen);
    free(seen_len);

    return count;
}

int main(void) {
    char *strs1[] = {"abc", "cba", "def", "fed", "xyz"};
    int n1 = 5;
    int result1 = count_reverse_pairs(strs1, n1);
    printf("%d\n", result1);

    char *strs2[] = {"aa", "aa", "bb", "bb"};
    int n2 = 4;
    int result2 = count_reverse_pairs(strs2, n2);
    printf("%d\n", result2);

    char *strs3[] = {"hello", "world", "dlrow", "olleh"};
    int n3 = 4;
    int result3 = count_reverse_pairs(strs3, n3);
    printf("%d\n", result3);

    char *strs4[] = {"a", "b", "c"};
    int n4 = 3;
    int result4 = count_reverse_pairs(strs4, n4);
    printf("%d\n", result4);

    return 0;
}