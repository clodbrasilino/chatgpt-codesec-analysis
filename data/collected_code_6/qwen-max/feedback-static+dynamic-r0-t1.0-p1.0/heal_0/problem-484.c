#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* remove_matching_tuples(Tuple *tuples1, int len1, Tuple *tuples2, int len2, int *new_len) {
    Tuple *result = (Tuple *)malloc(len1 * sizeof(Tuple));
    if (result == NULL) return NULL;
    *new_len = 0;

    for (int i = 0; i < len1; i++) {
        int found = 0;
        for (int j = 0; j < len2; j++) {
            if (tuples1[i].a == tuples2[j].a && tuples1[i].b == tuples2[j].b) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[(*new_len)++] = tuples1[i];
        }
    }

    return result;
}

int main() {
    Tuple tuples1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuples2[] = {{3, 4}, {7, 8}};
    int len1 = sizeof(tuples1) / sizeof(tuples1[0]);
    int len2 = sizeof(tuples2) / sizeof(tuples2[0]);
    int new_len;

    Tuple *result = remove_matching_tuples(tuples1, len1, tuples2, len2, &new_len);
    if (result == NULL) {
        return 1;
    }

    for (int i = 0; i < new_len; i++) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    free(result);
    return 0;
}