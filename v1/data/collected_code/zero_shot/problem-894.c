#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float real;
    float imag;
} Tuple;

Tuple convertToTuple(char* floatString) {
    Tuple tuple;
    
    char* token = strtok(floatString, " ");
    tuple.real = atof(token);
    
    token = strtok(NULL, " ");
    tuple.imag = atof(token);
    
    return tuple;
}

int main() {
    char floatString[] = "3.14 2.71";
    Tuple tuple = convertToTuple(floatString);
    printf("Real: %.2f\n", tuple.real);
    printf("Imaginary: %.2f\n", tuple.imag);
    
    return 0;
}