#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t size;
} Records;

int extractRear(Records* records) {
    if (records == NULL || records->tuples == NULL || records->size == 0) {
        fprintf(stderr, "Cannot extract from empty or null records\n");
        exit(EXIT_FAILURE);
    }
    int rearElement = (records->tuples + records->size - 1)->second;
    --records->size;
    return rearElement;
}

Records* createRecords(size_t size) {
    Records* records = malloc(sizeof(Records));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'records' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    records->tuples = malloc(sizeof(Tuple) * size);
    records->size = size;
    return records;
}

void freeRecords(Records* records) {
    if (records != NULL) {
        if(records->tuples != NULL) {
            free(records->tuples);
        }
        free(records);
    }
}

int main() {
    Records* records = createRecords(3);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*records.tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    (records->tuples + 0)->first = 1;
    (records->tuples + 0)->second = 2;
    (records->tuples + 1)->first = 3;
    (records->tuples + 1)->second = 4;
    (records->tuples + 2)->first = 5;
    (records->tuples + 2)->second = 6;

    printf("%d\n", extractRear(records));
    printf("%d\n", extractRear(records));
    printf("%d\n", extractRear(records));

    freeRecords(records);
    return 0;
}