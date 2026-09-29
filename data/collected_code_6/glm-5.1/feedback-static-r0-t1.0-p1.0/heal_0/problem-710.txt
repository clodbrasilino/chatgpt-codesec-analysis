#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} TupleRecord;

int get_first(const TupleRecord *rec, int *out) {
    if (!rec || !out || !rec->data || rec->size == 0) {
        return -1;
    }
    *out = rec->data[0];
    return 0;
}

int get_last(const TupleRecord *rec, int *out) {
    if (!rec || !out || !rec->data || rec->size == 0) {
        return -1;
    }
    *out = rec->data[rec->size - 1];
    return 0;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    TupleRecord rec = {arr, 5};

    int first_val;
    int last_val;

    if (get_first(&rec, &first_val) == 0) {
        printf("First: %d\n", first_val);
    }

    if (get_last(&rec, &last_val) == 0) {
        printf("Last: %d\n", last_val);
    }

    TupleRecord empty_rec = {NULL, 0};

    if (get_first(&empty_rec, &first_val) != 0) {
        printf("Empty record handled safely.\n");
    }

    return 0;
}