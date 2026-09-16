#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    const Tuple *t1 = (const Tuple *)a;
    const Tuple *t2 = (const Tuple *)b;
    if (t1->first < t2->first) return -1;
    if (t1->first > t2->first) return 1;
    return 0;
}

void sort_tuples(Tuple *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return;
    }
    qsort(arr, n, sizeof(Tuple), compare);
}

int main(void) {
    Tuple *arr = NULL;
    size_t n = 0;
    
    if (scanf("%zu", &n) != 1 || n == 0) {
        return 0;
    }
    
    if (n > SIZE_MAX / sizeof(Tuple)) {
        return 1;
    }
    
    arr = (Tuple *)malloc(n * sizeof(Tuple));
    if (arr == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d %d", &arr[i].first, &arr[i].second) != 2) {
            free(arr);
            return 1;
        }
    }
    
    sort_tuples(arr, n);
    
    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d)\n", arr[i].first, arr[i].second);
    }
    
    free(arr);
    arr = NULL;
    
    return 0;
}