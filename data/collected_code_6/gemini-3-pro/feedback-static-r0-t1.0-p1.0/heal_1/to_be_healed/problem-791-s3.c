#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
} NestedRecord;

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char data[50];
    NestedRecord* nested;
} Tuple;

void remove_nested_record(Tuple* tuple) {
    if (tuple != NULL && tuple->nested != NULL) {
        free(tuple->nested);
        tuple->nested = NULL;
    }
}

int main() {
    Tuple tuple;
    tuple.id = 1;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(tuple.data, "Tuple Data", sizeof(tuple.data) - 1);
    tuple.data[sizeof(tuple.data) - 1] = '\0';
    
    tuple.nested = (NestedRecord*)malloc(sizeof(NestedRecord));
    if (tuple.nested == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    tuple.nested->id = 2;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(tuple.nested->name, "Nested Data", sizeof(tuple.nested->name) - 1);
    tuple.nested->name[sizeof(tuple.nested->name) - 1] = '\0';
    
    remove_nested_record(&tuple);
    
    return 0;
}