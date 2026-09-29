#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} StringTuple;

StringTuple concat_string_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    StringTuple result;
    size_t i;
    
    if (tuple1 == NULL || tuple2 == NULL) {
        result.items = NULL;
        result.length = 0;
        return result;
    }
    
    result.length = tuple1->length + tuple2->length;
    result.items = (char **)malloc(result.length * sizeof(char *));
    
    if (result.items == NULL) {
        result.length = 0;
        return result;
    }
    
    for (i = 0; i < tuple1->length; i++) {
        size_t len = strnlen(tuple1->items[i], SIZE_MAX);
        /* Possible weaknesses found:
         *  alloc_size is assigned 'len+1' here.
         */
        size_t alloc_size = len + 1;
        
        /* Possible weaknesses found:
         *  Condition 'alloc_size<len' is always false [knownConditionTrueFalse]
         *  Condition 'alloc_size<len' is always false
         */
        if (alloc_size < len) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
        
        result.items[i] = (char *)malloc(alloc_size * sizeof(char));
        if (result.items[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
        
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.items[i], tuple1->items[i], len);
        }
        result.items[i][len] = '\0';
    }
    
    for (i = 0; i < tuple2->length; i++) {
        size_t index = tuple1->length + i;
        size_t len = strnlen(tuple2->items[i], SIZE_MAX);
        /* Possible weaknesses found:
         *  alloc_size is assigned 'len+1' here.
         */
        size_t alloc_size = len + 1;
        
        /* Possible weaknesses found:
         *  Condition 'alloc_size<len' is always false [knownConditionTrueFalse]
         *  Condition 'alloc_size<len' is always false
         */
        if (alloc_size < len) {
            size_t j;
            for (j = 0; j < index; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
        
        result.items[index] = (char *)malloc(alloc_size * sizeof(char));
        if (result.items[index] == NULL) {
            size_t j;
            for (j = 0; j < index; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
        
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.items[index], tuple2->items[i], len);
        }
        result.items[index][len] = '\0';
    }
    
    return result;
}

void free_string_tuple(StringTuple *tuple) {
    size_t i;
    
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    
    for (i = 0; i < tuple->length; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->length = 0;
}

int main(void) {
    char *items1[] = {"hello", "world"};
    char *items2[] = {"foo", "bar", "baz"};
    StringTuple tuple1;
    StringTuple tuple2;
    StringTuple result;
    size_t i;
    
    tuple1.items = items1;
    tuple1.length = 2;
    tuple2.items = items2;
    tuple2.length = 3;
    
    result = concat_string_tuples(&tuple1, &tuple2);
    
    if (result.items == NULL) {
        printf("Concatenation failed\n");
        return 1;
    }
    
    for (i = 0; i < result.length; i++) {
        printf("%s\n", result.items[i]);
    }
    
    free_string_tuple(&result);
    
    return 0;
}