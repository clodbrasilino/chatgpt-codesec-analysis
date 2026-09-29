#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.items = NULL;
    tuple.count = 0;
    
    if (str == NULL) {
        return tuple;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return tuple;
    }
    
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }
    strcpy(copy, str);
    
    size_t capacity = 4;
    tuple.items = malloc(capacity * sizeof(char *));
    if (tuple.items == NULL) {
        free(copy);
        return tuple;
    }
    
    char *token = strtok(copy, ",");
    while (token != NULL) {
        while (*token == ' ') token++;
        
        size_t token_len = strlen(token);
        while (token_len > 0 && token[token_len - 1] == ' ') {
            token[token_len - 1] = '\0';
            token_len--;
        }
        
        if (tuple.count == capacity) {
            capacity *= 2;
            char **new_items = realloc(tuple.items, capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.items[i]);
                }
                free(tuple.items);
                free(copy);
                tuple.items = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.items = new_items;
        }
        
        tuple.items[tuple.count] = malloc(strlen(token) + 1);
        if (tuple.items[tuple.count] == NULL) {
            for (size_t i = 0; i < tuple.count; i++) {
                free(tuple.items[i]);
            }
            free(tuple.items);
            free(copy);
            tuple.items = NULL;
            tuple.count = 0;
            return tuple;
        }
        strcpy(tuple.items[tuple.count], token);
        tuple.count++;
        
        token = strtok(NULL, ",");
    }
    
    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

int main(void) {
    const char *test_str = "apple, banana, cherry, date";
    Tuple result = string_to_tuple(test_str);
    
    printf("Tuple contains %zu items:\n", result.count);
    for (size_t i = 0; i < result.count; i++) {
        printf("  [%zu] = '%s'\n", i, result.items[i]);
    }
    
    free_tuple(&result);
    
    const char *empty_str = "";
    Tuple empty_result = string_to_tuple(empty_str);
    printf("Empty tuple contains %zu items\n", empty_result.count);
    free_tuple(&empty_result);
    
    const char *null_str = NULL;
    Tuple null_result = string_to_tuple(null_str);
    printf("Null tuple contains %zu items\n", null_result.count);
    free_tuple(&null_result);
    
    return 0;
}