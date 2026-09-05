#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* remove_matching_tuples(Tuple* t1, size_t* s1, Tuple* t2, size_t s2) {
    if (t1 == NULL || s1 == NULL || t2 == NULL) {
        return NULL;
    }

    size_t original_s1 = *s1;
    Tuple* result = (Tuple*)malloc(original_s1 * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < original_s1; i++) {
        int match = 0;
        for (size_t j = 0; j < s2; j++) {
            if (t1[i].a == t2[j].a && t1[i].b == t2[j].b) {
                match = 1;
                break;
            }
        }
        if (!match) {
            result[count++] = t1[i];
        }
    }

    if (count == 0) {
        free(result);
        *s1 = 0;
        return NULL;
    }

    Tuple* trimmed = (Tuple*)realloc(result, count * sizeof(Tuple));
    if (trimmed != NULL) {
        result = trimmed;
    }

    *s1 = count;
    return result;
}

int main() {
    Tuple t1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple t2[] = {{3, 4}, {7, 8}};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    size_t s2 = sizeof(t2) / sizeof(t2[0]);

    size_t res_size = s1;
    Tuple* res = remove_matching_tuples(t1, &res_size, t2, s2);

    for (size_t i = 0; i < res_size; i++) {
        printf("(%d, %d)\n", res[i].a, res[i].b);
    }

    free(res);

    return 0;
}