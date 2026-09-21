#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char value[100];
} Tuple;

Tuple* extract_singles(Tuple* tuples, int n, int* result_size) {
    Tuple* result = (Tuple*)malloc(n * sizeof(Tuple));
    if (result == NULL) return NULL;
    *result_size = 0;
    for (int i = 0; i < n; ++i) {
        int is_unique = 1;
        for (int j = 0; j < n; ++j) {
            if (i != j && tuples[i].key == tuples[j].key) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            result[(*result_size)++] = tuples[i];
        }
    }
    return realloc(result, (*result_size) * sizeof(Tuple));
}

int main() {
    Tuple tuples[] = {{1, "apple"}, {2, "banana"}, {1, "cherry"}, {3, "date"}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int result_size;
    Tuple* singles = extract_singles(tuples, n, &result_size);
    for (int i = 0; i < result_size; ++i) {
        printf("%d: %s\n", singles[i].key, singles[i].value);
    }
    free(singles);
    return 0;
}