#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[64];
} Tuple;

void clear_tuple(Tuple *t) {
    if (t == NULL) {
        return;
    }
    t->id = 0;
    t->value = 0.0;
    memset(t->name, 0, sizeof(t->name));
}

int main(void) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return EXIT_FAILURE;
    }
    
    tuple->id = 42;
    tuple->value = 3.14159;
    
    const char *source = "Sample Data";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t source_len = strlen(source);
    size_t copy_len = (source_len < sizeof(tuple->name) - 1) ? source_len : sizeof(tuple->name) - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->name, source, copy_len);
    tuple->name[copy_len] = '\0';
    
    printf("Before clearing: id=%d, value=%.5f, name=%s\n", 
           tuple->id, tuple->value, tuple->name);
    
    clear_tuple(tuple);
    
    printf("After clearing: id=%d, value=%.5f, name=%s\n", 
           tuple->id, tuple->value, tuple->name);
    
    free(tuple);
    tuple = NULL;
    
    return EXIT_SUCCESS;
}