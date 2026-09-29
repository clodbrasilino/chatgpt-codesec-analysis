#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int (*data)[3];
    size_t length;
} TupleList;

int compare(const void *a, const void *b) {
    const int *tupleA = (const int *)a;
    const int *tupleB = (const int *)b;
    return tupleA[2] - tupleB[2];
}

void sort_tuples(TupleList *list) {
    qsort(list->data, list->length, sizeof(int[3]), compare);
}

int main() {
    TupleList list = {NULL, 0};
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 1};
    int c[] = {7, 8, 2};

    /* Possible weaknesses found:
     *  (near initialization for 'tuples[0]')
     *  (near initialization for 'tuples[2]')
     *  (near initialization for 'tuples[1]')
     *  initialization of 'int (*)[3]' from incompatible pointer type 'int *' [-Wincompatible-pointer-types]
     */
    int (*tuples[])[3] = {a, b, c};
    /* Possible weaknesses found:
     *  assignment to 'int (*)[3]' from incompatible pointer type 'int (**)[3]' [-Wincompatible-pointer-types]
     */
    list.data = tuples;
    list.length = 3;

    sort_tuples(&list);

    for (size_t i = 0; i < list.length; ++i) {
        printf("(%d, %d, %d)\n", list.data[i][0], list.data[i][1], list.data[i][2]);
    }

    return 0;
}