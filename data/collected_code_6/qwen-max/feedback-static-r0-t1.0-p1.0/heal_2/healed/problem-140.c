#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char value[100];
} Tuple;

int compare_keys(const void* a, const void* b) {
    return ((Tuple*)a)->key - ((Tuple*)b)->key;
}

Tuple* extract_singles(Tuple* tuples, int n, int* result_size) {
    qsort(tuples, n, sizeof(Tuple), compare_keys);
    *result_size = 0;
    for (int i = 0; i < n; ) {
        int j = i + 1;
        while (j < n && tuples[i].key == tuples[j].key) j++;
        if (j - i == 1) {
            tuples[*result_size] = tuples[i];
            (*result_size)++;
        }
        i = j;
    }
    return realloc(tuples, (*result_size) * sizeof(Tuple));
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