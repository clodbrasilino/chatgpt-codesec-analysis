#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    int id;
    char *name;
    struct Record *nested;
} Record;

typedef struct Tuple {
    Record *record;
} Tuple;

Record* create_record(int id, const char *name) {
    Record *rec = (Record*)malloc(sizeof(Record));
    if (!rec) return NULL;
    rec->id = id;
    rec->name = (char*)malloc(strlen(name) + 1);
    if (!rec->name) {
        free(rec);
        return NULL;
    }
    strcpy(rec->name, name);
    rec->nested = NULL;
    return rec;
}

void free_record(Record *rec) {
    if (!rec) return;
    free(rec->name);
    free_record(rec->nested);
    free(rec);
}

Record* remove_nested_record(Tuple *tuple) {
    if (!tuple || !tuple->record) return NULL;
    Record *nested = tuple->record->nested;
    tuple->record->nested = NULL;
    return nested;
}

int main(void) {
    Tuple tuple;
    tuple.record = create_record(1, "Outer");
    if (!tuple.record) {
        return EXIT_FAILURE;
    }

    tuple.record->nested = create_record(2, "Inner");
    if (!tuple.record->nested) {
        free_record(tuple.record);
        return EXIT_FAILURE;
    }

    printf("Before: %s -> %s\n", tuple.record->name, tuple.record->nested->name);

    Record *removed = remove_nested_record(&tuple);
    if (removed) {
        printf("Removed nested: %s\n", removed->name);
        free_record(removed);
    }

    printf("After: %s (nested: %s)\n", tuple.record->name, 
           tuple.record->nested ? tuple.record->nested->name : "none");

    free_record(tuple.record);
    return EXIT_SUCCESS;
}