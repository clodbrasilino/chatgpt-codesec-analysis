#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Record {
    int id;
    char *name;
    struct Record *nested;
} Record;

typedef struct Tuple {
    Record *records;
    size_t size;
} Tuple;

Record *create_record(int id, const char *name, Record *nested) {
    Record *rec = (Record *)malloc(sizeof(Record));
    if (!rec) return NULL;
    rec->id = id;
    rec->name = (char *)malloc(strlen(name) + 1);
    if (!rec->name) {
        free(rec);
        return NULL;
    }
    strcpy(rec->name, name);
    rec->nested = nested;
    return rec;
}

void free_record(Record *rec) {
    if (!rec) return;
    free(rec->name);
    free(rec);
}

Tuple *create_tuple(size_t size) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->size = size;
    t->records = (Record *)calloc(size, sizeof(Record));
    if (!t->records && size > 0) {
        free(t);
        return NULL;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (!t) return;
    for (size_t i = 0; i < t->size; i++) {
        free_record(t->records[i].nested);
        free(t->records[i].name);
    }
    free(t->records);
    free(t);
}

int remove_nested_record(Tuple *tuple, size_t index) {
    if (!tuple || index >= tuple->size) return -1;
    Record *rec = &tuple->records[index];
    if (rec->nested) {
        free_record(rec->nested);
        rec->nested = NULL;
        return 0;
    }
    return -2;
}

int main(void) {
    Tuple *tuple = create_tuple(3);
    if (!tuple) return 1;

    tuple->records[0].id = 1;
    tuple->records[0].name = (char *)malloc(8);
    if (!tuple->records[0].name) {
        free_tuple(tuple);
        return 1;
    }
    strcpy(tuple->records[0].name, "alpha");
    tuple->records[0].nested = create_record(10, "nested1", NULL);

    tuple->records[1].id = 2;
    tuple->records[1].name = (char *)malloc(8);
    if (!tuple->records[1].name) {
        free_record(tuple->records[0].nested);
        free(tuple->records[0].name);
        free_tuple(tuple);
        return 1;
    }
    strcpy(tuple->records[1].name, "beta");
    tuple->records[1].nested = NULL;

    tuple->records[2].id = 3;
    tuple->records[2].name = (char *)malloc(8);
    if (!tuple->records[2].name) {
        free_record(tuple->records[0].nested);
        free(tuple->records[0].name);
        free(tuple->records[1].name);
        free_tuple(tuple);
        return 1;
    }
    strcpy(tuple->records[2].name, "gamma");
    tuple->records[2].nested = create_record(20, "nested2", NULL);

    int result = remove_nested_record(tuple, 0);
    printf("remove_nested_record returned: %d\n", result);

    result = remove_nested_record(tuple, 1);
    printf("remove_nested_record returned: %d\n", result);

    free_tuple(tuple);
    return 0;
}