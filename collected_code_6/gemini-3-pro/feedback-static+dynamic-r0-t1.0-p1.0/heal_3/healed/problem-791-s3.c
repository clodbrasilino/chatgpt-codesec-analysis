#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
} NestedRecord;

typedef struct {
    int id;
    char *data;
    NestedRecord* nested;
} Tuple;

void remove_nested_record(Tuple* tuple) {
    if (tuple != NULL && tuple->nested != NULL) {
        if (tuple->nested->name != NULL) {
            free(tuple->nested->name);
        }
        free(tuple->nested);
        tuple->nested = NULL;
    }
}

int main(void) {
    Tuple tuple;
    const char *data_str = "Tuple Data";
    size_t data_sz = sizeof("Tuple Data");
    
    const char *nested_str = "Nested Data";
    size_t nested_sz = sizeof("Nested Data");
    
    tuple.id = 1;
    
    tuple.data = (char *)malloc(data_sz);
    if (tuple.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    snprintf(tuple.data, data_sz, "%s", data_str);
    
    tuple.nested = (NestedRecord *)malloc(sizeof(NestedRecord));
    if (tuple.nested == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple.data);
        return 1;
    }
    
    tuple.nested->id = 2;
    
    tuple.nested->name = (char *)malloc(nested_sz);
    if (tuple.nested->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple.nested);
        free(tuple.data);
        return 1;
    }
    
    snprintf(tuple.nested->name, nested_sz, "%s", nested_str);
    
    remove_nested_record(&tuple);
    free(tuple.data);
    
    return 0;
}