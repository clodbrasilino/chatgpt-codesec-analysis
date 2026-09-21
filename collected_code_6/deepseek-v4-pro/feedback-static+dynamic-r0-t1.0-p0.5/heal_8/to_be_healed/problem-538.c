#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Tuple string_list_to_tuple(char **list, size_t count) {
    Tuple tuple;
    tuple.size = count;
    
    if (count == 0 || list == NULL) {
        tuple.items = NULL;
        tuple.size = 0;
        return tuple;
    }
    
    if (count > SIZE_MAX / sizeof(char *)) {
        tuple.items = NULL;
        tuple.size = 0;
        return tuple;
    }
    
    tuple.items = (char **)malloc(count * sizeof(char *));
    if (tuple.items == NULL) {
        tuple.size = 0;
        return tuple;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        
        size_t len = safe_strlen(list[i], SIZE_MAX - 1);
        
        if (len >= SIZE_MAX - 1) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        
        tuple.items[i] = (char *)malloc(len + 1);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }
        
        if (len > 0) {
            if (len <= SIZE_MAX) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(tuple.items[i], list[i], len);
            }
        }
        tuple.items[i][len] = '\0';
    }
    
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

int main(void) {
    char *list[] = {"hello", "world", "tuple", "example"};
    size_t count = sizeof(list) / sizeof(list[0]);
    
    Tuple tuple = string_list_to_tuple(list, count);
    if (tuple.items == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    printf("Tuple contents:\n");
    for (size_t i = 0; i < tuple.size; i++) {
        printf("  [%zu] %s\n", i, tuple.items[i]);
    }
    
    free_tuple(&tuple);
    return 0;
}