#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} TupleRecord;

int get_initial(TupleRecord *t) {
    if (t == NULL || t->data == NULL || t->size == 0) {
        return -1;
    }
    return t->data[0];
}

int get_last(TupleRecord *t) {
    if (t == NULL || t->data == NULL || t->size == 0) {
        return -1;
    }
    return t->data[t->size - 1];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    TupleRecord t;
    t.data = arr;
    /* Possible weaknesses found:
     *  Assignment 't.size=sizeof(arr)/sizeof(arr[0])', assigned value is 5
     */
    t.size = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  Condition 't.size==0' is always false [knownConditionTrueFalse]
     *  Condition 't.size==0' is always false
     */
    if (t.data == NULL || t.size == 0) {
        return EXIT_FAILURE;
    }

    int initial = get_initial(&t);
    int last = get_last(&t);

    printf("Initial: %d\n", initial);
    printf("Last: %d\n", last);

    return EXIT_SUCCESS;
}