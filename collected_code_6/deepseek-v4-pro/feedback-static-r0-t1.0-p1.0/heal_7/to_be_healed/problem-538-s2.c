#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} Tuple;

Tuple string_list_to_tuple(char **list, size_t length) {
    Tuple tuple;
    tuple.length = 0;
    tuple.items = NULL;

    if (length == 0 || list == NULL) {
        return tuple;
    }

    if (length > SIZE_MAX / sizeof(char *)) {
        return tuple;
    }

    tuple.items = (char **)malloc(length * sizeof(char *));
    
    if (tuple.items == NULL) {
        return tuple;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t item_len = strlen(list[i]);
        
        if (item_len >= SIZE_MAX) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }

        /* Possible weaknesses found:
         *  Assignment 'dest_size=item_len+1', assigned value is greater than 0
         */
        size_t dest_size = item_len + 1;
        
        /* Possible weaknesses found:
         *  Condition 'dest_size==0' is always false
         *  Condition 'dest_size==0' is always false [knownConditionTrueFalse]
         */
        if (dest_size == 0) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }

        tuple.items[i] = (char *)malloc(dest_size);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.length = 0;
            return tuple;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple.items[i], list[i], item_len);
        tuple.items[i][item_len] = '\0';
    }
    
    tuple.length = length;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    
    for (size_t i = 0; i < tuple->length; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->length = 0;
}

int main(void) {
    char *list[] = {"hello", "world", "example", "tuple"};
    size_t length = sizeof(list) / sizeof(list[0]);
    
    Tuple tuple = string_list_to_tuple(list, length);
    
    if (tuple.items == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    printf("Tuple contents:\n");
    for (size_t i = 0; i < tuple.length; i++) {
        printf("[%zu] %s\n", i, tuple.items[i]);
    }
    
    free_tuple(&tuple);
    return 0;
}