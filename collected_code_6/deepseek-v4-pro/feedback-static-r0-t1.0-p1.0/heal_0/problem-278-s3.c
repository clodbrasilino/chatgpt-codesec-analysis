#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
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
    
    return 0;
}

int main(void) {
    Tuple tuple;
    tuple.size = 5;
    tuple.elements = malloc(tuple.size * sizeof(Record));
    
    if (tuple.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    tuple.elements[0] = (Record){101, "Alpha", 10.5f};
    tuple.elements[1] = (Record){102, "Beta", 20.5f};
    tuple.elements[2] = (Record){103, "Gamma", 30.5f};
    tuple.elements[3] = (Record){104, "Delta", 40.5f};
    tuple.elements[4] = (Record){105, "Epsilon", 50.5f};
    
    size_t result = count_before_record(&tuple, 103);
    printf("Elements before record with id 103: %zu\n", result);
    
    result = count_before_record(&tuple, 999);
    printf("Elements before record with id 999: %zu\n", result);
    
    free(tuple.elements);
    tuple.elements = NULL;
    tuple.size = 0;
    
    return 0;
}