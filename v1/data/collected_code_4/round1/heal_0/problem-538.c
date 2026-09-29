#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char **items;
    int length;
} Tuple;

Tuple* convert_to_tuple(char **str_list, int list_length){
    if(!str_list || list_length <= 0) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if(!tuple) {
        return NULL;
    }
    
    tuple->items = (char**)malloc(sizeof(char*) * list_length);
    if(!tuple->items) {
        free(tuple);
        return NULL;
    }
    
    for(int i = 0; i < list_length; i++) {
        tuple->items[i] = strdup(str_list[i]);
        if(!tuple->items[i]) {
            for(int j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
    }
    tuple->length = list_length;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if(NULL == tuple) {
        return;
    }
    
    for(int i = 0; i < tuple->length; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main() {
    char* str_list[] = {"apple", "banana", "cherry"};

    Tuple *tuple = convert_to_tuple(str_list, 3);
    if(!tuple) {
        fprintf(stderr, "Failed to convert string list to tuple.\n");
        return 1;
    }
    
    for(int i = 0; i < tuple->length; i++){
        printf("%s\n", tuple->items[i]);
    }
    
    free_tuple(tuple);
    return 0;
}