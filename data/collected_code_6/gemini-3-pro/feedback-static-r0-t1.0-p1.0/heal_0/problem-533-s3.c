#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    FLOAT,
    CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char c;
    } data;
} TupleElement;

typedef struct {
    TupleElement* elements;
    size_t size;
} Tuple;

Tuple* createTuple(size_t size) {
    if (size == 0) {
        return NULL;
    }
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->elements = (TupleElement*)malloc(size * sizeof(TupleElement));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }
    tuple->size = size;
    return tuple;
}

void freeTuple(Tuple* tuple) {
    if (tuple) {
        if (tuple->elements) {
            free(tuple->elements);
        }
        free(tuple);
    }
}

Tuple* removeElementsOfType(const Tuple* inputTuple, DataType typeToRemove) {
    if (!inputTuple || !inputTuple->elements) {
        return NULL;
    }

    size_t newSize = 0;
    for (size_t i = 0; i < inputTuple->size; ++i) {
        if (inputTuple->elements[i].type != typeToRemove) {
            newSize++;
        }
    }

    Tuple* newTuple = createTuple(newSize);
    if (!newTuple && newSize > 0) {
        return NULL;
    }

    if (newSize > 0) {
        size_t index = 0;
        for (size_t i = 0; i < inputTuple->size; ++i) {
            if (inputTuple->elements[i].type != typeToRemove) {
                newTuple->elements[index++] = inputTuple->elements[i];
            }
        }
    }

    return newTuple;
}

void printTuple(const Tuple* tuple) {
    if (!tuple || !tuple->elements || tuple->size == 0) {
        printf("Empty Tuple\n");
        return;
    }
    for (size_t i = 0; i < tuple->size; ++i) {
        switch (tuple->elements[i].type) {
            case INT:
                printf("INT: %d\n", tuple->elements[i].data.i);
                break;
            case FLOAT:
                printf("FLOAT: %f\n", tuple->elements[i].data.f);
                break;
            case CHAR:
                printf("CHAR: %c\n", tuple->elements[i].data.c);
                break;
        }
    }
}

int main(void) {
    Tuple* myTuple = createTuple(5);
    if (!myTuple) {
        return EXIT_FAILURE;
    }

    myTuple->elements[0].type = INT;
    myTuple->elements[0].data.i = 10;
    
    myTuple->elements[1].type = FLOAT;
    myTuple->elements[1].data.f = 3.14f;
    
    myTuple->elements[2].type = CHAR;
    myTuple->elements[2].data.c = 'a';
    
    myTuple->elements[3].type = INT;
    myTuple->elements[3].data.i = 20;
    
    myTuple->elements[4].type = FLOAT;
    myTuple->elements[4].data.f = 2.71f;

    Tuple* filteredTuple = removeElementsOfType(myTuple, INT);
    if (!filteredTuple && myTuple->size > 0 && filteredTuple != NULL) {
        freeTuple(myTuple);
        return EXIT_FAILURE;
    }

    printTuple(filteredTuple);

    freeTuple(myTuple);
    freeTuple(filteredTuple);

    return EXIT_SUCCESS;
}