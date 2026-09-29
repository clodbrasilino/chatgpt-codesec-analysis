#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
} Tuple;

int compareTuples(const void *t1, const void *t2) {
    const Tuple *tuple1 = (const Tuple *)t1;
    const Tuple *tuple2 = (const Tuple *)t2;
    if (tuple1->a == tuple2->a && tuple1->b == tuple2->b) return 0;
    return 1;
}

void findSimilarElements(Tuple *list1, Tuple *list2, int size1, int size2, Tuple **result, int *resultSize) {
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if (compareTuples(&list1[i], &list2[j]) == 0) {
                (*result)[*resultSize] = list1[i];
                (*resultSize)++;
            }
        }
    }
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{3, 4}, {7, 8}, {1, 2}};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int maxResultSize = size1 > size2 ? size1 : size2;
    Tuple *result = (Tuple *)malloc(maxResultSize * sizeof(Tuple));
    int resultSize = 0;

    findSimilarElements(list1, list2, size1, size2, &result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    free(result);
    return 0;
}