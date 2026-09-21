#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LENGTH];
    float value;
} Record;

typedef struct {
    Record *elements;
    size_t size;
} Tuple;

size_t count_before_record(const Tuple *tuple, int target_id) {
    if (tuple == NULL || tuple->elements == NULL) {
        return 0;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i].id == target_id) {
            return count;
        }
        count++;
    }
    
    return tuple->size;
}

Record create_record(int id, const char *name, float value) {
    Record record;
    record.id = id;
    record.value = value;
    
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t name_len = strlen(name);
        if (name_len >= MAX_NAME_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(record.name, name, MAX_NAME_LENGTH - 1);
            record.name[MAX_NAME_LENGTH - 1] = '\0';
        } else {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(record.name, name, name_len);
            record.name[name_len] = '\0';
        }
    } else {
        record.name[0] = '\0';
    }
    
    return record;
}

int main(void) {
    Tuple tuple;
    tuple.size = 5;
    tuple.elements = malloc(tuple.size * sizeof(Record));
    
    if (tuple.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    tuple.elements[0] = create_record(101, "Alpha", 10.5f);
    tuple.elements[1] = create_record(102, "Beta", 20.5f);
    tuple.elements[2] = create_record(103, "Gamma", 30.5f);
    tuple.elements[3] = create_record(104, "Delta", 40.5f);
    tuple.elements[4] = create_record(105, "Epsilon", 50.5f);
    
    size_t result = count_before_record(&tuple, 103);
    printf("Elements before record with id 103: %zu\n", result);
    
    result = count_before_record(&tuple, 999);
    printf("Elements before record with id 999: %zu\n", result);
    
    free(tuple.elements);
    tuple.elements = NULL;
    tuple.size = 0;
    
    return 0;
}