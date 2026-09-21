#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NAME_SIZE 32

typedef struct {
    int id;
    float value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_SIZE];
} Record;

typedef struct {
    int type;
    Record *nested;
    int data;
} Tuple;

void remove_nested_record(Tuple *t)
{
    if (t == NULL) {
        return;
    }
    
    if (t->nested != NULL) {
        free(t->nested);
        t->nested = NULL;
    }
}

Tuple* create_tuple(int type, int data, int id, float value, const char *name)
{
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (name != NULL && strlen(name) >= NAME_SIZE) {
        return NULL;
    }
    
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    
    t->type = type;
    t->data = data;
    t->nested = NULL;
    
    Record *rec = malloc(sizeof(Record));
    if (rec == NULL) {
        free(t);
        return NULL;
    }
    
    rec->id = id;
    rec->value = value;
    
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(name);
        if (len >= NAME_SIZE) {
            len = NAME_SIZE - 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(rec->name, name, len);
        rec->name[len] = '\0';
    } else {
        rec->name[0] = '\0';
    }
    
    t->nested = rec;
    
    return t;
}

void print_tuple(const Tuple *t)
{
    if (t == NULL) {
        printf("Tuple is NULL\n");
        return;
    }
    
    printf("Type: %d, Data: %d\n", t->type, t->data);
    
    if (t->nested != NULL) {
        printf("Nested Record - ID: %d, Value: %.2f, Name: %s\n",
               t->nested->id, t->nested->value, t->nested->name);
    } else {
        printf("Nested Record: NULL\n");
    }
}

int main(void)
{
    Tuple *tuple = create_tuple(1, 100, 42, 3.14f, "TestRecord");
    
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("Before removal:\n");
    print_tuple(tuple);
    
    remove_nested_record(tuple);
    
    printf("\nAfter removal:\n");
    print_tuple(tuple);
    
    free(tuple);
    
    return EXIT_SUCCESS;
}