#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float value;
} FloatTuple;

FloatTuple str_to_float_tuple(const char *str) {
    FloatTuple tuple;
    tuple.value = atof(str);
    return tuple;
}

int main() {
    const char *input = "3.14";
    FloatTuple result = str_to_float_tuple(input);
    printf("Converted float: %f\n", result.value);
    return 0;
}