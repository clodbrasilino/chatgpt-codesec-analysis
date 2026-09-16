#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} TupleRecord;

void get_initial_and_last(const TupleRecord *record, int *initial, int *last) {
    if (record == NULL || initial == NULL || last == NULL) {
        abort();
    }
    if (record->size == 0 || record->data == NULL) {
        abort();
    }
    *initial = record->data[0];
    *last = record->data[record->size - 1];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    TupleRecord record = {arr, 5};
    int initial, last;

    get_initial_and_last(&record, &initial, &last);
    printf("Initial: %d, Last: %d\n", initial, last);

    return 0;
}