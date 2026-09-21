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
    if (!name) return NULL;
    
    size_t name_len = strnlen(name, 256);
    if (name_len > 255) name_len = 255;
    
    Record *rec = (Record *)malloc(sizeof(Record));
    if (!rec) return NULL;
    rec->id = id;
    
    rec->name = (char *)malloc(name_len + 1);
    if (!rec->name) {
        free(rec);
        return NULL;
    }
    
    memcpy(rec->name, name, name_len);
    rec->name[name_len] = '\0';
    rec->nested = nested;
    return rec;
}

Record *clone_record(Record *src) {
    if (!src || !src->name) return NULL;
    
    size_t name_len = strnlen(src->name, 256);
    
    Record *clone = (Record *)malloc(sizeof(Record));
    if (!clone) return NULL;
    
    clone->id = src->id;
    
    clone->name = (char *)malloc(name_len + 1);
    if (!clone->name) {
        free(clone);
        return NULL;
    }
    
    memcpy(clone->name, src->name, name_len);
    clone->name[name_len] = '\0';
    
    if (src->nested) {
        clone->nested = clone_record(src->nested);
    } else {
        clone->nested = NULL;
    }
    
    return clone;
}

void free_record(Record *rec) {
    if (!rec) return;
    free(rec->name);
    rec->name = NULL;
    if (rec->nested) {
        free_record(rec->nested);
        rec->nested = NULL;
    }
    free(rec);
}

void free_record_contents(Record *rec) {
    if (!rec) return;
    free(rec->name);
    rec->name = NULL;
    if (rec->nested) {
        free_record(rec->nested);
        rec->nested = NULL;
    }
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
        free(t->records[i].name);
        if (t->records[i].nested) {
            free_record(t->records[i].nested);
        }
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

    Record *r0 = create_record(1, "alpha", NULL);
    if (!r0) {
        free_tuple(tuple);
        return 1;
    }
    
    free_record_contents(&tuple->records[0]);
    
    tuple->records[0].id = r0->id;
    size_t name_len = strnlen(r0->name, 256);
    tuple->records[0].name = (char *)malloc(name_len + 1);
    if (!tuple->records[0].name) {
        free_record(r0);
        free_tuple(tuple);
        return 1;
    }
    memcpy(tuple->records[0].name, r0->name, name_len);
    tuple->records[0].name[name_len] = '\0';
    tuple->records[0].nested = NULL;
    
    free_record(r0);
    
    tuple->records[0].nested = create_record(10, "nested1", NULL);

    Record *r1 = create_record(2, "beta", NULL);
    if (!r1) {
        free_tuple(tuple);
        return 1;
    }
    
    free_record_contents(&tuple->records[1]);
    
    tuple->records[1].id = r1->id;
    name_len = strnlen(r1->name, 256);
    tuple->records[1].name = (char *)malloc(name_len + 1);
    if (!tuple->records[1].name) {
        free_record(r1);
        free_tuple(tuple);
        return 1;
    }
    memcpy(tuple->records[1].name, r1->name, name_len);
    tuple->records[1].name[name_len] = '\0';
    tuple->records[1].nested = NULL;
    
    free_record(r1);

    Record *r2 = create_record(3, "gamma", NULL);
    if (!r2) {
        free_tuple(tuple);
        return 1;
    }
    
    free_record_contents(&tuple->records[2]);
    
    tuple->records[2].id = r2->id;
    name_len = strnlen(r2->name, 256);
    tuple->records[2].name = (char *)malloc(name_len + 1);
    if (!tuple->records[2].name) {
        free_record(r2);
        free_tuple(tuple);
        return 1;
    }
    memcpy(tuple->records[2].name, r2->name, name_len);
    tuple->records[2].name[name_len] = '\0';
    tuple->records[2].nested = NULL;
    
    free_record(r2);
    
    tuple->records[2].nested = create_record(20, "nested2", NULL);

    int result = remove_nested_record(tuple, 0);
    printf("remove_nested_record returned: %d\n", result);

    result = remove_nested_record(tuple, 1);
    printf("remove_nested_record returned: %d\n", result);

    free_tuple(tuple);
    return 0;
}