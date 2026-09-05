#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Record;

typedef struct {
    int key;
    Record* records;
    int record_count;
} Tuple;

int find_max_value_in_records(Tuple* tuples, int tuple_count) {
    int max_val = tuples[0].records[0].value;
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i].records == NULL || tuples[i].record_count <= 0) {
            continue;
        }
        for (int j = 0; j < tuples[i].record_count; j++) {
            if (tuples[i].records[j].value > max_val) {
                max_val = tuples[i].records[j].value;
            }
        }
    }
    return max_val;
}

void free_tuples(Tuple* tuples, int tuple_count) {
    for (int i = 0; i < tuple_count; i++) {
        free(tuples[i].records);
        tuples[i].records = NULL;
    }
    free(tuples);
}

int main() {
    int tuple_count = 3;
    Tuple* tuples = (Tuple*)malloc(tuple_count * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    tuples[0].key = 1;
    tuples[0].record_count = 2;
    tuples[0].records = (Record*)malloc(2 * sizeof(Record));
    if (tuples[0].records == NULL) {
        free_tuples(tuples, 0);
        return 1;
    }
    tuples[0].records[0].id = 10;
    tuples[0].records[0].value = 42;
    tuples[0].records[1].id = 11;
    tuples[0].records[1].value = 85;

    tuples[1].key = 2;
    tuples[1].record_count = 3;
    tuples[1].records = (Record*)malloc(3 * sizeof(Record));
    if (tuples[1].records == NULL) {
        free_tuples(tuples, 1);
        return 1;
    }
    tuples[1].records[0].id = 20;
    tuples[1].records[0].value = 33;
    tuples[1].records[1].id = 21;
    tuples[1].records[1].value = 102;
    tuples[1].records[2].id = 22;
    tuples[1].records[2].value = 76;

    tuples[2].key = 3;
    tuples[2].record_count = 0;
    tuples[2].records = NULL;

    int max = find_max_value_in_records(tuples, tuple_count);
    printf("%d\n", max);

    free_tuples(tuples, tuple_count);

    return 0;
}