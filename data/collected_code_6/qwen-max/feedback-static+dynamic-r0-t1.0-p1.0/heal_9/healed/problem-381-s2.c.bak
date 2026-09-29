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
        char *pivot = p + (nmemb / 2) * size;
        char tmp[size];

        memcpy(tmp, pivot, size);
        char *store = p;
        for (char *ptr = p; ptr < p + nmemb * size; ptr += size) {
            if (compar(ptr, tmp, arg) < 0) {
                memcpy(store, ptr, size);
                store += size;
            }
        }
        memcpy(pivot, tmp, size);
        memmove(pivot, store, (p + nmemb * size - store));
        store -= size;
        memmove(store, tmp, size);

        qsort_r(p, (store - p) / size, size, compar, arg);
        qsort_r(p + (store - p + size), (p + nmemb * size - store) / size, size, compar, arg);
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