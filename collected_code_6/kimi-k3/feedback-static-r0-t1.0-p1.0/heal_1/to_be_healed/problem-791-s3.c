#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[32];
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
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    
    t->type = type;
    t->data = data;
    t->nested = malloc(sizeof(Record));
    
    if (t->nested == NULL) {
        free(t);
        return NULL;
    }
    
    t->nested->id = id;
    t->nested->value = value;
    
    if (name != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(t->nested->name, name, sizeof(t->nested->name) - 1);
        t->nested->name[sizeof(t->nested->name) - 1] = '\0';
    } else {
        t->nested->name[0] = '\0';
    }
    
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