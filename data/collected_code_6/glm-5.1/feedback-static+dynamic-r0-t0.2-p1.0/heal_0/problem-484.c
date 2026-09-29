#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* remove_matching_tuples(const Tuple* t1, size_t len1, const Tuple* t2, size_t len2, size_t* out_len) {
    Tuple* result = (Tuple*)malloc(len1 * sizeof(Tuple));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < len1; i++) {
        int match = 0;
        for (size_t j = 0; j < len2; j++) {
            if (t1[i].a == t2[j].a && t1[i].b == t2[j].b) {
                match = 1;
                break;
            }
        }
        if (!match) {
            result[count] = t1[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *out_len = 0;
        return NULL;
    }

    Tuple* trimmed = (Tuple*)realloc(result, count * sizeof(Tuple));
    if (trimmed != NULL) {
        result = trimmed;
    }

    *out_len = count;
    return result;
}

int main() {
    Tuple t1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple t2[] = {{3, 4}, {7, 8}, {9, 10}};
    size_t len1 = sizeof(t1) / sizeof(t1[0]);
    size_t len2 = sizeof(t2) / sizeof(t2[0]);
    size_t out_len = 0;

    Tuple* result = remove_matching_tuples(t1, len1, t2, len2, &out_len);

    for (size_t i = 0; i < out_len; i++) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    if (result != NULL) {
        free(result);
    }

    return 0;
}