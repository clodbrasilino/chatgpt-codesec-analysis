#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compareTuples(const void *t1, const void *t2) {
    const Tuple *tuple1 = t1;
    const Tuple *tuple2 = t2;
    if (tuple1->a == tuple2->a && tuple1->b == tuple2->b) return 0;
    if (tuple1->a < tuple2->a || (tuple1->a == tuple2->a && tuple1->b < tuple2->b)) return -1;
    return 1;
}

int findIntersection(Tuple *list1, int size1, Tuple *list2, int size2, Tuple **result) {
    qsort(list1, size1, sizeof(Tuple), compareTuples);
    qsort(list2, size2, sizeof(Tuple), compareTuples);

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        int cmp = compareTuples(&list1[i], &list2[j]);
        if (cmp == 0) {
            result[k++] = &list1[i];
            i++;
            j++;
        } else if (cmp < 0) {
            i++;
        } else {
            j++;
        }
    }
    return k;
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{2, 1}, {3, 4}, {7, 8}};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    Tuple *result[size1 + size2];
    int count = findIntersection(list1, size1, list2, size2, result);

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", result[i]->a, result[i]->b);
    }

    return 0;
}