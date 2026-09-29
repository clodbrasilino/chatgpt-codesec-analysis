#include <stdio.h>
#include <stdlib.h>

// Defining a struct to mimic a tuple
typedef struct Tuple {
    int *intElement;
    float *floatElement;
    char *charElement;
} Tuple;

// Function to initialize a tuple
void initializeTuple(Tuple *tuple, int intValue, float floatValue, char charValue) {
    tuple->intElement = (int *)malloc(sizeof(int));
    tuple->floatElement = (float *)malloc(sizeof(float));
    tuple->charElement = (char *)malloc(sizeof(char));
    *(tuple->intElement) = intValue;
    *(tuple->floatElement) = floatValue;
    *(tuple->charElement) = charValue;
}

// Function to delete particular elements depending upon the datatype
void removeElement(Tuple *tuple, char dataType) {
    switch(dataType) {
        case 'i':
            free(tuple->intElement);
            tuple->intElement = NULL;
            break;
        case 'f':
            free(tuple->floatElement);
            tuple->floatElement = NULL;
            break;
        case 'c':
            free(tuple->charElement);
            tuple->charElement = NULL;
            break;
        default:
            printf("Invalid data type.\n");
    }
}

// Function to print tuple values
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

// A main function for testing
int main() {
    Tuple myTuple;
    initializeTuple(&myTuple, 5, 7.3, 'a');
    printTuple(&myTuple);
    removeElement(&myTuple, 'i');
    printTuple(&myTuple);
    return 0;
}