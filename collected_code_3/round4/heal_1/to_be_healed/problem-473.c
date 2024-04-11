#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* findIntersection(Tuple* list1, int size1, Tuple* list2, int size2, int* returnSize) {
    int i, j, k = 0;
    Tuple* result = (Tuple*)malloc(sizeof(Tuple) * ((size1 < size2) ? size1 : size2));

    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if((list1[i].first == list2[j].first && list1[i].second == list2[j].second) ||
               (list1[i].first == list2[j].second && list1[i].second == list2[j].first)) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                result[k].first = list1[i].first;
                result[k].second = list1[i].second;
                k++;
                break;
            }
        }
    }

    *returnSize = k;
    return result;
}

int main() {
    int i, returnSize;
    Tuple list1[] = {{1, 2}, {2, 3}, {3, 4}};
    Tuple list2[] = {{2, 1}, {3, 2}, {4, 3}};
    int size1 = sizeof(list1) / sizeof(Tuple);
    int size2 = sizeof(list2) / sizeof(Tuple);

    Tuple* result = findIntersection(list1, size1, list2, size2, &returnSize);

    for(i = 0; i < returnSize; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    free(result);
    return 0;
}