#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple *convertArrayToTuple(int *array, size_t length) {
    if(array == NULL || length < 2) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if(tuple == NULL) {
        return NULL;
    }
    
    tuple->a = array[0];
    tuple->b = array[1];
    
    return tuple;
}

int main() {
    int values[2] = {5, 7};
    
    Tuple* tuple = convertArrayToTuple(values, 2);
    if(tuple == NULL) {
        printf("Conversion Failed\n");
        return 1;
    }
    
    printf("Tuple: (%d, %d)\n", tuple->a, tuple->b);
    
    free(tuple);
    
    return 0;
}