#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

TupleList trim_tuples(TupleList list, int k) {
    TupleList result;
    result.count = list.count;
    result.tuples = (Tuple *)malloc(sizeof(Tuple) * list.count);
    
    if (result.tuples == NULL) {
        result.count = 0;
        return result;
    }
    
    for (int i = 0; i < list.count; i++) {
        int new_size = list.tuples[i].size - k;
        if (new_size < 0) {
            new_size = 0;
        }
        
        result.tuples[i].size = new_size;
        result.tuples[i].elements = (int *)malloc(sizeof(int) * new_size);
        
        if (result.tuples[i].elements == NULL && new_size > 0) {
            for (int j = 0; j < i; j++) {
                free(result.tuples[j].elements);
            }
            free(result.tuples);
            result.count = 0;
            result.tuples = NULL;
            return result;
        }
        
        for (int j = 0; j < new_size; j++) {
            result.tuples[i].elements[j] = list.tuples[i].elements[j];
        }
    }
    
    return result;
}

void free_tuple_list(TupleList list) {
    if (list.tuples != NULL) {
        for (int i = 0; i < list.count; i++) {
            if (list.tuples[i].elements != NULL) {
                free(list.tuples[i].elements);
            }
        }
        free(list.tuples);
    }
}

int main(void) {
    TupleList input;
    input.count = 3;
    input.tuples = (Tuple *)malloc(sizeof(Tuple) * input.count);
    
    if (input.tuples == NULL) {
        return 1;
    }
    
    input.tuples[0].size = 5;
    input.tuples[0].elements = (int *)malloc(sizeof(int) * 5);
    input.tuples[1].size = 3;
    input.tuples[1].elements = (int *)malloc(sizeof(int) * 3);
    input.tuples[2].size = 4;
    input.tuples[2].elements = (int *)malloc(sizeof(int) * 4);
    
    if (input.tuples[0].elements == NULL || input.tuples[1].elements == NULL || input.tuples[2].elements == NULL) {
        free_tuple_list(input);
        return 1;
    }
    
    for (int i = 0; i < 5; i++) input.tuples[0].elements[i] = i + 1;
    for (int i = 0; i < 3; i++) input.tuples[1].elements[i] = i + 10;
    for (int i = 0; i < 4; i++) input.tuples[2].elements[i] = i + 20;
    
    TupleList result = trim_tuples(input, 2);
    
    if (result.tuples == NULL && result.count == 0) {
        free_tuple_list(input);
        return 1;
    }
    
    for (int i = 0; i < result.count; i++) {
        printf("Tuple %d: ", i);
        for (int j = 0; j < result.tuples[i].size; j++) {
            printf("%d ", result.tuples[i].elements[j]);
        }
        printf("\n");
    }
    
    free_tuple_list(input);
    free_tuple_list(result);
    
    return 0;
}