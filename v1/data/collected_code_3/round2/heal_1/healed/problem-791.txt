#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int *nestedRecord;
    int nestedRecordSize;
} Tuple;

void removeNestedRecord(Tuple *tuple) {
    free(tuple->nestedRecord);
    tuple->nestedRecord = NULL;
    tuple->nestedRecordSize = 0;
}

int main() {
    Tuple tuple;
    tuple.id = 1;
    tuple.nestedRecordSize = 5;
    tuple.nestedRecord = (int*) malloc(tuple.nestedRecordSize * sizeof(int));

    if(tuple.nestedRecord != NULL) {
        for(int i = 0; i < tuple.nestedRecordSize; i++) {
            tuple.nestedRecord[i] = i;
        }

        removeNestedRecord(&tuple);
    }

    if(tuple.nestedRecord == NULL) {
        printf("Nested record removed successfully.\n");
    } else {
        printf("Failed to remove nested record.\n");
    }

    return 0;
}