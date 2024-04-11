#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int intVal;
    float floatVal;
    char charVal;
    int type; // 0 for int, 1 for float, 2 for char
} TupleElement;

typedef struct {
    TupleElement* elements;
    int size;
} Tuple;

Tuple* removeDataType(Tuple* tuple, int typeToRemove) {
    int i, j = 0;
    TupleElement* newElements = (TupleElement*) malloc(tuple->size * sizeof(TupleElement));
    for(i = 0; i < tuple->size; i++) {
        if(tuple->elements[i].type != typeToRemove) {
            newElements[j++] = tuple->elements[i];
        }
    }
    Tuple* newTuple = (Tuple*) malloc(sizeof(Tuple));
    newTuple->elements = newElements;
    newTuple->size = j;
    return newTuple;
}

int main() {
    Tuple tuple;
    tuple.size = 3;
    tuple.elements = (TupleElement*) malloc(tuple.size * sizeof(TupleElement));
    tuple.elements[0].intVal = 1;
    tuple.elements[0].type = 0;
    tuple.elements[1].floatVal = 2.0;
    tuple.elements[1].type = 1;
    tuple.elements[2].charVal = 'a';
    tuple.elements[2].type = 2;

    Tuple* newTuple = removeDataType(&tuple, 1);
    int i;
    for(i = 0; i < newTuple->size; i++) {
        if(newTuple->elements[i].type == 0) {
            printf("%d ", newTuple->elements[i].intVal);
        } else if(newTuple->elements[i].type == 2) {
            printf("%c ", newTuple->elements[i].charVal);
        }
    }
    free(tuple.elements);
    free(newTuple->elements);
    free(newTuple);
    return 0;
}