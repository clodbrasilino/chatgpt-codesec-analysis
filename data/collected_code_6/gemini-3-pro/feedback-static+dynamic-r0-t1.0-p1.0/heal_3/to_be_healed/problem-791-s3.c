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
    const char *nested_str = "Nested Data";
    
    tuple.id = 1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    tuple.data = (char *)malloc(strlen(data_str) + 1);
    if (tuple.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(tuple.data, data_str);
    
    tuple.nested = (NestedRecord *)malloc(sizeof(NestedRecord));
    if (tuple.nested == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple.data);
        return 1;
    }
    
    tuple.nested->id = 2;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    tuple.nested->name = (char *)malloc(strlen(nested_str) + 1);
    if (tuple.nested->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple.nested);
        free(tuple.data);
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(tuple.nested->name, nested_str);
    
    remove_nested_record(&tuple);
    free(tuple.data);
    
    return 0;
}