#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* name;
} NestedRecord;

typedef struct {
    int id;
    char* data;
    NestedRecord* nested;
} Tuple;

void remove_nested_record(Tuple* tuple) {
    if (tuple != NULL && tuple->nested != NULL) {
        if (tuple->nested->name != NULL) {
            free(tuple->nested->name);
            tuple->nested->name = NULL;
        }
        free(tuple->nested);
        tuple->nested = NULL;
    }
}

int main(void) {
    Tuple tuple;
    const char* tuple_data_str = "Tuple Data";
    const char* nested_name_str = "Nested Data";

    tuple.id = 1;
    
    tuple.data = (char*)malloc(strlen(tuple_data_str) + 1);
    if (tuple.data != NULL) {
        snprintf(tuple.data, strlen(tuple_data_str) + 1, "%s", tuple_data_str);
    }
    
    tuple.nested = (NestedRecord*)malloc(sizeof(NestedRecord));
    if (tuple.nested == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        if (tuple.data != NULL) {
            free(tuple.data);
        }
        return 1;
    }
    
    tuple.nested->id = 2;
    
    tuple.nested->name = (char*)malloc(strlen(nested_name_str) + 1);
    if (tuple.nested->name != NULL) {
        snprintf(tuple.nested->name, strlen(nested_name_str) + 1, "%s", nested_name_str);
    }
    
    remove_nested_record(&tuple);
    
    if (tuple.data != NULL) {
        free(tuple.data);
        tuple.data = NULL;
    }
    
    return 0;
}