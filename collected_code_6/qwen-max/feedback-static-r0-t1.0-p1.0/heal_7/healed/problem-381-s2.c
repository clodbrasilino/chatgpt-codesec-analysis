#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

int compare(const void *a, const void *b, void *arg) {
    size_t index = *(size_t *)arg;
    return ((IntList *)a)->data[index] - ((IntList *)b)->data[index];
}

void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg) {
    if (nmemb > 1) {
        char *p = (char *)base;
        size_t k = 0;
        for (size_t i = 1; i < nmemb; i++) {
            if (compar(p + (k * size), p + (i * size), arg) > 0) {
                k = i;
            }
        }
        char tmp[size];
        memcpy(tmp, p + (k * size), size);
        memmove(p + k * size, p, k * size);
        memcpy(p, tmp, size);
        qsort_r(p + size, k, size, compar, arg);
        qsort_r(p + k * size + size, nmemb - k - 1, size, compar, arg);
    }
}

void sort_lists_by_index(IntList *lists, size_t list_count, size_t index) {
    qsort_r(lists, list_count, sizeof(IntList), compare, &index);
}

int main() {
    IntList lists[3] = {
        { .data = (int[]){5, 2, 8}, .size = 3 },
        { .data = (int[]){1, 4, 3}, .size = 3 },
        { .data = (int[]){9, 7, 6}, .size = 3 }
    };
    size_t list_count = 3;
    size_t index = 1;

    sort_lists_by_index(lists, list_count, index);

    for (size_t i = 0; i < list_count; i++) {
        for (size_t j = 0; j < lists[i].size; j++) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}