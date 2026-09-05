#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    if (tupleA->second < tupleB->second) return -1;
    if (tupleA->second > tupleB->second) return 1;
    return 0;
}

void sort_tuples(Tuple *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return;
    }
    qsort(arr, n, sizeof(Tuple), compare);
}

int main(void) {
    Tuple arr[] = {{1, 5}, {2, 3}, {3, 8}, {4, 1}, {5, 7}};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    sort_tuples(arr, n);
    
    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d) ", arr[i].first, arr[i].second);
    }
    printf("\n");
    
    return 0;
}