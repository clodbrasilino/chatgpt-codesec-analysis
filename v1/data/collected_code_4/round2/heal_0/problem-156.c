#include <stdio.h>
#include <stdlib.h>

typedef struct tuple_string {
    char* first;
    char* second;
} TupleString;

typedef struct tuple_integer {
    int first;
    int second;
} TupleInt;

TupleInt string_to_int(TupleString input) {
    TupleInt output;
    
    if(input.first != NULL) {
        output.first = atoi(input.first);
    } else {
        output.first = 0;
    }

    if(input.second != NULL) {
        output.second = atoi(input.second);
    } else {
        output.second = 0;
    }

    return output;
}

int main() {
    TupleString input;
    input.first = "123";
    input.second = "456";

    TupleInt output = string_to_int(input);

    printf("First integer: %d, Second integer: %d\n", output.first, output.second);

    return 0;
}