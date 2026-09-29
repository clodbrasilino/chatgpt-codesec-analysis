#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} tuple;

int compare_tuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    tuple *tupleA = (tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    tuple *tupleB = (tuple *)b;
    return (*(tupleA->elements + tupleA->length - 1) - *(tupleB->elements + tupleB->length - 1));
}

void sort_tuples(tuple *tuples, size_t count) {
    qsort(tuples, count, sizeof(tuple), compare_tuples);
}

int main() {
    tuple tuples[] = {
        /* Possible weaknesses found:
         *  (near initialization for 'tuples[0].elements')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{1, 3, 5}, 3},
        /* Possible weaknesses found:
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  (near initialization for 'tuples[1].elements')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{2, 4, 1}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'tuples[2].elements')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        {{7, 8, 9}, 3}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, count);

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < tuples[i].length; j++) {
            printf("%d ", tuples[i].elements[j]);
        }
        printf("\n");
    }

    return 0;
}