#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *arr;
    size_t len;
} List;

int compare(const void *a, const void *b) {
    const List *ia = (const List *)a;
    const List *ib = (const List *)b;

    if (ia->len < ib->len) return -1;
    if (ia->len > ib->len) return  1;

    for (size_t i = 0; i < ia->len; i++) {
        if (ia->arr[i] < ib->arr[i]) return -1;
        if (ia->arr[i] > ib->arr[i]) return  1;
    }

    return 0;
}

int main() {
    List lists[3];

    int arr1[] = {1,23,44,56};
    lists[0].arr = arr1;
    lists[0].len = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {5,10,15};
    lists[1].arr = arr2;
    lists[1].len = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {7,14};
    lists[2].arr = arr3;
    lists[2].len = sizeof(arr3) / sizeof(arr3[0]);

    size_t list_len = sizeof(lists)/sizeof(lists[0]);
    
    qsort(lists, list_len, sizeof(List), compare);

    for (size_t i = 0; i < list_len; i++) {
        for (size_t j = 0; j < lists[i].len; j++) {
            printf("%d ", lists[i].arr[j]);
        }
        printf("\n");
    }
    return 0;
}