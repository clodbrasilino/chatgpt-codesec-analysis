#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int id;
    char *name;
    double *values;
    size_t value_count;
} Tuple;

void clear_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    
    if (tuple->name != NULL) {
        free(tuple->name);
        tuple->name = NULL;
    }
    
    if (tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
    }
    
    tuple->id = 0;
    tuple->value_count = 0;
}

void clear_tuples(Tuple *tuples, size_t tuple_count) {
    size_t i;
    
    if (tuples == NULL) {
        return;
    }
    
    for (i = 0; i < tuple_count; i++) {
        clear_tuple(&tuples[i]);
    }
}

Tuple *create_tuple(int id, const char *name, const double *values, size_t value_count) {
    Tuple *tuple;
    /* Possible weaknesses found:
     *  The scope of the variable 'name_len' can be reduced. [variableScope]
     */
    size_t name_len;
    size_t i;
    
    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->id = id;
    tuple->name = NULL;
    tuple->values = NULL;
    tuple->value_count = 0;
    
    if (name != NULL) {
        name_len = 0;
        while (name[name_len] != '\0') {
            if (name_len == SIZE_MAX) {
                free(tuple);
                return NULL;
            }
            name_len++;
        }
        
        tuple->name = (char *)malloc(name_len + 1);
        if (tuple->name == NULL) {
            free(tuple);
            return NULL;
        }
        
        for (i = 0; i < name_len; i++) {
            tuple->name[i] = name[i];
        }
        tuple->name[name_len] = '\0';
    }
    
    if (values != NULL && value_count > 0) {
        if (value_count > SIZE_MAX / sizeof(double)) {
            free(tuple->name);
            free(tuple);
            return NULL;
        }
        tuple->values = (double *)malloc(value_count * sizeof(double));
        if (tuple->values == NULL) {
            free(tuple->name);
            free(tuple);
            return NULL;
        }
        for (i = 0; i < value_count; i++) {
            tuple->values[i] = values[i];
        }
        tuple->value_count = value_count;
    }
    
    return tuple;
}

int main(void) {
    Tuple *tuples[3];
    const double values1[] = {1.5, 2.5, 3.5};
    const double values2[] = {4.5, 5.5};
    size_t i;
    
    tuples[0] = create_tuple(1, "First", values1, 3);
    tuples[1] = create_tuple(2, "Second", values2, 2);
    tuples[2] = create_tuple(3, NULL, NULL, 0);
    
    if (tuples[0] == NULL || tuples[1] == NULL || tuples[2] == NULL) {
        for (i = 0; i < 3; i++) {
            if (tuples[i] != NULL) {
                clear_tuple(tuples[i]);
                free(tuples[i]);
            }
        }
        return 1;
    }
    
    printf("Before clear:\n");
    for (i = 0; i < 3; i++) {
        printf("Tuple %zu: id=%d, name=%s, value_count=%zu\n",
               i, tuples[i]->id,
               tuples[i]->name != NULL ? tuples[i]->name : "NULL",
               tuples[i]->value_count);
    }
    
    clear_tuples(tuples[0], 3);
    
    printf("\nAfter clear:\n");
    for (i = 0; i < 3; i++) {
        printf("Tuple %zu: id=%d, name=%s, value_count=%zu\n",
               i, tuples[i]->id,
               tuples[i]->name != NULL ? tuples[i]->name : "NULL",
               tuples[i]->value_count);
    }
    
    for (i = 0; i < 3; i++) {
        free(tuples[i]);
    }
    
    return 0;
}