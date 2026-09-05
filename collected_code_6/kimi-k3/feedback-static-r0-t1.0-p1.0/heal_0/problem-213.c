#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} StringTuple;

StringTuple* concatenate_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL || 
        tuple1->first == NULL || tuple1->second == NULL ||
        tuple2->first == NULL || tuple2->second == NULL) {
        return NULL;
    }

    size_t len1 = strlen(tuple1->first);
    size_t len2 = strlen(tuple1->second);
    size_t len3 = strlen(tuple2->first);
    size_t len4 = strlen(tuple2->second);

    if (len1 > SIZE_MAX - len3 - 1 || len2 > SIZE_MAX - len4 - 1) {
        return NULL;
    }

    StringTuple *result = malloc(sizeof(StringTuple));
    if (result == NULL) {
        return NULL;
    }

    result->first = malloc(len1 + len3 + 1);
    if (result->first == NULL) {
        free(result);
        return NULL;
    }

    result->second = malloc(len2 + len4 + 1);
    if (result->second == NULL) {
        free(result->first);
        free(result);
        return NULL;
    }

    strcpy(result->first, tuple1->first);
    strcat(result->first, tuple2->first);
    strcpy(result->second, tuple1->second);
    strcat(result->second, tuple2->second);

    return result;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        free(tuple);
    }
}

int main(void) {
    StringTuple tuple1 = {"Hello", "World"};
    StringTuple tuple2 = {"Foo", "Bar"};
    
    StringTuple *result = concatenate_tuples(&tuple1, &tuple2);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to concatenate tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("First: %s\n", result->first);
    printf("Second: %s\n", result->second);
    
    free_tuple(result);
    
    return EXIT_SUCCESS;
}