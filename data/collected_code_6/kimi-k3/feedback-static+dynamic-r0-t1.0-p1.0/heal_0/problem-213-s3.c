#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    size_t count;
} StringTuple;

StringTuple *concatenate_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL || 
        (tuple1->count > 0 && tuple1->strings == NULL) || 
        (tuple2->count > 0 && tuple2->strings == NULL)) {
        return NULL;
    }

    if (tuple1->count > SIZE_MAX - tuple2->count) {
        return NULL;
    }

    size_t total_count = tuple1->count + tuple2->count;
    
    StringTuple *result = malloc(sizeof(StringTuple));
    if (result == NULL) {
        return NULL;
    }

    result->count = total_count;
    result->strings = NULL;

    if (total_count == 0) {
        return result;
    }

    result->strings = malloc(total_count * sizeof(char *));
    if (result->strings == NULL) {
        free(result);
        return NULL;
    }

    size_t i;
    for (i = 0; i < total_count; i++) {
        result->strings[i] = NULL;
    }

    size_t index = 0;
    
    for (i = 0; i < tuple1->count; i++) {
        if (tuple1->strings[i] == NULL) {
            continue;
        }
        result->strings[index] = malloc(strlen(tuple1->strings[i]) + 1);
        if (result->strings[index] == NULL) {
            for (size_t j = 0; j < index; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        strcpy(result->strings[index], tuple1->strings[i]);
        index++;
    }

    for (i = 0; i < tuple2->count; i++) {
        if (tuple2->strings[i] == NULL) {
            continue;
        }
        result->strings[index] = malloc(strlen(tuple2->strings[i]) + 1);
        if (result->strings[index] == NULL) {
            for (size_t j = 0; j < index; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        strcpy(result->strings[index], tuple2->strings[i]);
        index++;
    }

    result->count = index;
    return result;
}

void free_tuple(StringTuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->strings != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
    }
    free(tuple);
}

int main(void) {
    char *data1[] = {"Hello", "World", "From"};
    char *data2[] = {"C", "Programming", "Language"};
    
    StringTuple tuple1 = {data1, 3};
    StringTuple tuple2 = {data2, 3};
    
    StringTuple *result = concatenate_tuples(&tuple1, &tuple2);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to concatenate tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("Concatenated tuple contents:\n");
    for (size_t i = 0; i < result->count; i++) {
        printf("[%zu]: %s\n", i, result->strings[i]);
    }
    
    free_tuple(result);
    
    return EXIT_SUCCESS;
}