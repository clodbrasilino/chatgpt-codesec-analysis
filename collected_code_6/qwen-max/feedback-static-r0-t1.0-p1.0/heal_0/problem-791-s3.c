#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char *name;
} Record;

typedef struct {
    Record mainRecord;
    Record *nestedRecord;
} Tuple;

void free_tuple(Tuple *t) {
    if (t == NULL) return;
    free(t->mainRecord.name);
    free(t->nestedRecord->name);
    free(t->nestedRecord);
    free(t);
}

Tuple* remove_nested_record(Tuple *t) {
    if (t == NULL || t->nestedRecord == NULL) return t;
    free(t->nestedRecord->name);
    free(t->nestedRecord);
    t->nestedRecord = NULL;
    return t;
}

int main() {
    Record r1 = {1, strdup("MainRecord")};
    Record r2 = {2, strdup("NestedRecord")};
    Tuple t = {r1, &r2};

    Tuple *newTuple = remove_nested_record(&t);

    printf("Main Record ID: %d\n", newTuple->mainRecord.id);
    if (newTuple->nestedRecord) {
        printf("Nested Record ID: %d\n", newTuple->nestedRecord->id);
    } else {
        printf("Nested Record removed.\n");
    }

    free(newTuple->mainRecord.name);
    free(newTuple);
    return 0;
}