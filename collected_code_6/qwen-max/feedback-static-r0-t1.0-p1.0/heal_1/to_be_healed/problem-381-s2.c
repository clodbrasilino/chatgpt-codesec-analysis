#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memcpy'
  */

typedef struct {
    int *data;
    size_t size;
} IntList;

int compare(const void *a, const void *b, void *arg) {
    size_t index = *(size_t *)arg;
    return ((IntList *)a)->data[index] - ((IntList *)b)->data[index];
}

/* Possible weaknesses found:
 *  conflicting types for 'qsort_r'; have 'void(void *, size_t,  size_t,  int (*)(const void *, const void *, void *), void *)' {aka 'void(void *, long unsigned int,  long unsigned int,  int (*)(const void *, const void *, void *), void *)'}
 *  conflicting types for 'qsort_r'
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
        char tmp[size];
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
         *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        memcpy(tmp, p + (k * size), size);
        /* Possible weaknesses found:
         *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'memmove'
         *  include '<string.h>' or provide a declaration of 'memmove'
         */
        memmove(p + size, p, k * size);
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