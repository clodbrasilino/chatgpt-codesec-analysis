#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    
    if (!name) {
        rec->name = NULL;
    } else {
        size_t name_len = strnlen(name, 4096);
        if (name_len >= 4096) {
            free(rec);
            return NULL;
        }
        if (name_len > SIZE_MAX - 1) {
            free(rec);
            return NULL;
        }
        rec->name = (char *)malloc(name_len + 1);
        if (!rec->name) {
            free(rec);
            return NULL;
        }
        if (name_len > 0) {
            size_t dest_size = name_len + 1;
            if (name_len > dest_size) {
                free(rec->name);
                free(rec);
                return NULL;
            }
            memcpy(rec->name, name, name_len);
        }
        rec->name[name_len] = '\0';
    }
    
    rec->nested = nested;
    return rec;
}

void free_record(Record *rec) {
    if (!rec) return;
    free(rec->name);
    if (rec->nested) {
        free_record(rec->nested);
    }
    free(rec);
}

Tuple *create_tuple(size_t size) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->size = size;
    if (size == 0) {
        t->records = NULL;
    } else {
        if (size > SIZE_MAX / sizeof(Record)) {
            free(t);
            return NULL;
        }
        t->records = (Record *)calloc(size, sizeof(Record));
        if (!t->records) {
            free(t);
            return NULL;
        }
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

static char *safe_strdup(const char *src, size_t max_len) {
    if (!src) return NULL;
    size_t len = strnlen(src, max_len);
    if (len >= max_len) return NULL;
    if (len > SIZE_MAX - 1) return NULL;
    char *dst = (char *)malloc(len + 1);
    if (!dst) return NULL;
    if (len > 0) {
        size_t dest_size = len + 1;
        if (len > dest_size) {
            free(dst);
            return NULL;
        }
        memcpy(dst, src, len);
    }
    dst[len] = '\0';
    return dst;
}

int main(void) {
    Tuple *tuple = create_tuple(3);
    if (!tuple) return 1;

    tuple->records[0].id = 1;
    tuple->records[0].name = safe_strdup("alpha", 4096);
    if (!tuple->records[0].name) {
        free_tuple(tuple);
        return 1;
    }
    tuple->records[0].nested = create_record(10, "nested1", NULL);

    tuple->records[1].id = 2;
    tuple->records[1].name = safe_strdup("beta", 4096);
    if (!tuple->records[1].name) {
        free_tuple(tuple);
        return 1;
    }
    tuple->records[1].nested = NULL;

    tuple->records[2].id = 3;
    tuple->records[2].name = safe_strdup("gamma", 4096);
    if (!tuple->records[2].name) {
        free_tuple(tuple);
        return 1;
    }
    tuple->records[2].nested = create_record(20, "nested2", NULL);

    int result = remove_nested_record(tuple, 0);
    printf("remove_nested_record returned: %d\n", result);

    result = remove_nested_record(tuple, 1);
    printf("remove_nested_record returned: %d\n", result);

    free_tuple(tuple);
    return 0;
}