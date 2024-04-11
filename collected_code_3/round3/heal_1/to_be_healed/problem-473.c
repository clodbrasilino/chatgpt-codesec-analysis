#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* tuple_intersection(Tuple* list1, int size1, Tuple* list2, int size2, int* resultSize) {
    int i, j, k = 0;
    Tuple* result = (Tuple*)malloc(sizeof(Tuple) * ((size1 < size2) ? size1 : size2));

    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if((list1[i].a == list2[j].a && list1[i].b == list2[j].b) || 
               (list1[i].a == list2[j].b && list1[i].b == list2[j].a)) {
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                result[k++] = list1[i];
                break;
            }
        }
    }

    *resultSize = k;
    return result;
}

int main() {
    int i, size;
    Tuple list1[] = {{1, 2}, {2, 3}, {3, 4}};
    Tuple list2[] = {{2, 1}, {3, 2}, {4, 5}};
    Tuple* result = tuple_intersection(list1, 3, list2, 3, &size);

    for(i = 0; i < size; i++) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    free(result);
    return 0;
}