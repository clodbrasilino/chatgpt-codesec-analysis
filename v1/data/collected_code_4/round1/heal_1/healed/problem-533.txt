#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *intElement;
    float *floatElement;
    char *charElement;
} Tuple;

void initializeTuple(Tuple *tuple, int intValue, float floatValue, char charValue) {
    tuple->intElement = (int *)malloc(sizeof(int));
    tuple->floatElement = (float *)malloc(sizeof(float));
    tuple->charElement = (char *)malloc(sizeof(char));

    if(tuple->intElement != NULL) {
        *(tuple->intElement) = intValue;
    }

    if(tuple->floatElement != NULL) {
        *(tuple->floatElement) = floatValue;
    }

    if(tuple->charElement != NULL) {
        *(tuple->charElement) = charValue;
    }
}

void removeElement(Tuple *tuple, char dataType) {
    switch(dataType) {
        case 'i':
            if(tuple->intElement != NULL) {
                free(tuple->intElement);
                tuple->intElement = NULL;
            }
            break;
        case 'f':
            if(tuple->floatElement != NULL) {
                free(tuple->floatElement);
                tuple->floatElement = NULL;
            }
            break;
        case 'c':
            if(tuple->charElement != NULL) {
                free(tuple->charElement);
                tuple->charElement = NULL;
            }
            break;
        default:
            printf("Invalid data type.\n");
    }
}

void printTuple(Tuple *tuple) {
    if(tuple->intElement != NULL) {
        printf("Integer: %d\n", *(tuple->intElement));
    }
    if(tuple->floatElement != NULL) {
        printf("Float: %f\n", *(tuple->floatElement));
    }
    if(tuple->charElement != NULL) {
        printf("Char: %c\n", *(tuple->charElement));
    }
}

int main() {
    Tuple myTuple;
    initializeTuple(&myTuple, 5, 7.3, 'a');
    printTuple(&myTuple);
    removeElement(&myTuple, 'i');
    printTuple(&myTuple);
    return 0;
}