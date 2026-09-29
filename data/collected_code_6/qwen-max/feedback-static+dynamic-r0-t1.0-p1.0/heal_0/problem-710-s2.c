#include <stdio.h>
#include <stddef.h>

typedef struct {
    int data[5];
} TupleRecord;

void accessTupleData(TupleRecord *record, int *first, int *last) {
    if (record == NULL || first == NULL || last == NULL) return;
    *first = record->data[0];
    *last = record->data[sizeof(record->data)/sizeof(record->data[0]) - 1];
}

int main() {
    TupleRecord record = {{1, 2, 3, 4, 5}};
    int first, last;
    
    accessTupleData(&record, &first, &last);
    printf("First: %d, Last: %d\n", first, last);

    return 0;
}