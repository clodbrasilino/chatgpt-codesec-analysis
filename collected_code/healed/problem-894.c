#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float real;
    float imag;
} Tuple;

Tuple convertToTuple(const char* floatString) {
    Tuple tuple;
    char* copyFloatString = strdup(floatString);
    
    char* token = strtok(copyFloatString, " ");
    tuple.real = atof(token);
    
    token = strtok(NULL, " ");
    tuple.imag = atof(token);

    free(copyFloatString);
    
    return tuple;
}

int main() {
    const char floatString[] = "3.14 2.71";
    Tuple tuple = convertToTuple(floatString);
    printf("Real: %.2f\n", tuple.real);
    printf("Imaginary: %.2f\n", tuple.imag);
    
    return 0;
}