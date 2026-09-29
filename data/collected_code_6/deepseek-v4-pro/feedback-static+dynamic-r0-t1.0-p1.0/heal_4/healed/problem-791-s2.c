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
    Record *rec = NULL;
    size_t name_len;
    char *name_copy = NULL;

    if (!name) return NULL;

    name_len = strnlen(name, 1024);
    if (name_len >= 1024) {
        return NULL;
    }

    rec = (Record*)malloc(sizeof(Record));
    if (!rec) return NULL;

    name_copy = (char*)malloc(name_len + 1);
    if (!name_copy) {
        free(rec);
        return NULL;
    }

    memcpy(name_copy, name, name_len);
    name_copy[name_len] = '\0';

    rec->id = id;
    rec->name = name_copy;
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