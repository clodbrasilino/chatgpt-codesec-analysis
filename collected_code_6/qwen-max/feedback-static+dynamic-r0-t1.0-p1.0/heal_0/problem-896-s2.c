#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} TupleList;

int compare(const void *a, const void *b) {
    int *tupleA = *(int **)a;
    int *tupleB = *(int **)b;
    return tupleA[2] - tupleB[2];
}

void sort_tuples(TupleList *list) {
    qsort(list->data, list->length, sizeof(int *), compare);
}

int main() {
    TupleList list = {NULL, 0};
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 1};
    int c[] = {7, 8, 2};

    int *tuples[] = {a, b, c};
    list.data = tuples;
    list.length = 3;

    sort_tuples(&list);

    for (size_t i = 0; i < list.length; ++i) {
        printf("(%d, %d, %d)\n", list.data[i][0], list.data[i][1], list.data[i][2]);
    }

    return 0;
}