#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compare(const void *x, const void *y) {
    const Tuple *t1 = (const Tuple *)x;
    const Tuple *t2 = (const Tuple *)y;
    if (t1->b < t2->b) return -1;
    if (t1->b > t2->b) return 1;
    return 0;
}

void sort_by_last_element(Tuple *arr, size_t n) {
    if (n == 0) return;
    qsort(arr, n, sizeof(Tuple), compare);
}

int main(void) {
    Tuple arr[] = {{2, 8}, {1, 2}, {3, 5}, {4, 1}};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    sort_by_last_element(arr, n);

    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d)\n", arr[i].a, arr[i].b);
    }

    return 0;
}