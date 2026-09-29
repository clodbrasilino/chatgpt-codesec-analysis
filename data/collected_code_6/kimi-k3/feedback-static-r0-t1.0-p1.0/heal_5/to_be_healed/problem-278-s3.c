#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[64];
    float value;
} Record;

typedef struct {
    Record *records;
    size_t count;
    size_t capacity;
} Tuple;

int tuple_init(Tuple *t, size_t initial_capacity)
{
    if (t == NULL || initial_capacity == 0) {
        return -1;
    }
    if (initial_capacity > SIZE_MAX / sizeof(Record)) {
        return -1;
    }
    t->records = calloc(initial_capacity, sizeof(Record));
    if (t->records == NULL) {
        return -1;
    }
    t->count = 0;
    t->capacity = initial_capacity;
    return 0;
}

void tuple_free(Tuple *t)
{
    if (t != NULL && t->records != NULL) {
        free(t->records);
        t->records = NULL;
        t->count = 0;
        t->capacity = 0;
    }
}

int tuple_add(Tuple *t, int id, const char *name, float value)
{
    size_t name_len;
    
    if (t == NULL || name == NULL) {
        return -1;
    }
    
    name_len = strnlen(name, sizeof(t->records[0].name));
    if (name_len >= sizeof(t->records[0].name)) {
        return -1;
    }
    
    if (t->count >= t->capacity) {
        size_t new_capacity = t->capacity * 2;
        Record *new_records;
        if (new_capacity < t->capacity || new_capacity > SIZE_MAX / sizeof(Record)) {
            return -1;
        }
        new_records = realloc(t->records, new_capacity * sizeof(Record));
        if (new_records == NULL) {
            return -1;
        }
        t->records = new_records;
        t->capacity = new_capacity;
    }
    
    t->records[t->count].id = id;
    snprintf(t->records[t->count].name, sizeof(t->records[t->count].name), "%s", name);
    t->records[t->count].value = value;
    t->count++;
    return 0;
}

size_t count_elements_before(const Tuple *t, const Record *target)
{
    size_t i;
    if (t == NULL || target == NULL || t->records == NULL) {
        return 0;
    }
    for (i = 0; i < t->count; i++) {
        if (t->records[i].id == target->id &&
            strcmp(t->records[i].name, target->name) == 0 &&
            fabsf(t->records[i].value - target->value) < 0.0001f) {
            return i;
        }
    }
    return t->count;
}

int main(void)
{
    Tuple t;
    Record target = {3, "Charlie", 30.5f};
    size_t before_count;

    if (tuple_init(&t, 4) != 0) {
        fprintf(stderr, "Failed to initialize tuple\n");
        return EXIT_FAILURE;
    }

    if (tuple_add(&t, 1, "Alice", 10.5f) != 0 ||
        tuple_add(&t, 2, "Bob", 20.3f) != 0 ||
        tuple_add(&t, 3, "Charlie", 30.5f) != 0 ||
        tuple_add(&t, 4, "David", 40.1f) != 0) {
        fprintf(stderr, "Failed to add records\n");
        tuple_free(&t);
        return EXIT_FAILURE;
    }

    before_count = count_elements_before(&t, &target);

    printf("Element count before target record: %zu\n", before_count);

    tuple_free(&t);
    return EXIT_SUCCESS;
}