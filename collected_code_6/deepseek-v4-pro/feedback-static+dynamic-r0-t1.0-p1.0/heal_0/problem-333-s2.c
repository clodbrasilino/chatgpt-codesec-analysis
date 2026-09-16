#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} Pair;

int compare_pairs(const void *a, const void *b) {
    const Pair *pair_a = (const Pair *)a;
    const Pair *pair_b = (const Pair *)b;
    
    if (pair_a->size < 2 && pair_b->size < 2) return 0;
    if (pair_a->size < 2) return -1;
    if (pair_b->size < 2) return 1;
    
    if (pair_a->arr[1] < pair_b->arr[1]) return -1;
    if (pair_a->arr[1] > pair_b->arr[1]) return 1;
    return 0;
}

void sort_by_second_element(Pair *list, int list_size) {
    if (list == NULL || list_size <= 1) return;
    qsort(list, list_size, sizeof(Pair), compare_pairs);
}

int main(void) {
    int data1[] = {1, 4};
    int data2[] = {2, 2};
    int data3[] = {3, 5};
    int data4[] = {4, 1};
    int data5[] = {5, 3};
    
    Pair list[] = {
        {data1, 2},
        {data2, 2},
        {data3, 2},
        {data4, 2},
        {data5, 2}
    };
    
    int list_size = sizeof(list) / sizeof(list[0]);
    
    sort_by_second_element(list, list_size);
    
    for (int i = 0; i < list_size; i++) {
        if (list[i].size >= 2) {
            printf("(%d, %d)\n", list[i].arr[0], list[i].arr[1]);
        }
    }
    
    return 0;
}