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

/* Possible weaknesses found:
 *  conflicting types for 'qsort_r'
 *  conflicting types for 'qsort_r'; have 'void(void *, size_t,  size_t,  int (*)(const void *, const void *, void *), void *)' {aka 'void(void *, long unsigned int,  long unsigned int,  int (*)(const void *, const void *, void *), void *)'}
 */
void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg) {
    if (nmemb > 1) {
        char *p = (char *)base;
        size_t i, k;
        for (i = 1, k = 0; i < nmemb; i++) {
            if (compar(p + (k * size), p + (i * size), arg) > 0) {
                k = i;
            }
        }
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char tmp[size];
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tmp, p + (k * size), size);
        memmove(p + size, p, k * size);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(p, tmp, size);
        qsort_r(p + size, nmemb - 1, size, compar, arg);
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