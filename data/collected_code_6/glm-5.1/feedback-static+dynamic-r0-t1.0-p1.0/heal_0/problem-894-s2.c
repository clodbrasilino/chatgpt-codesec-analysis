#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int integer_part;
    int fractional_part;
} FloatTuple;

FloatTuple convert_to_tuple(const char *str) {
    FloatTuple tuple = {0, 0};
    char *endptr;
    double val = strtod(str, &endptr);

    if (endptr == str) {
        return tuple;
    }

    tuple.integer_part = (int)val;
    double fractional = val - (double)tuple.integer_part;
    if (fractional < 0) {
        fractional = -fractional;
    }
    tuple.fractional_part = (int)(fractional * 1000000);

    return tuple;
}

int main(void) {
    const char *input = "-123.456789";
    FloatTuple result = convert_to_tuple(input);
    printf("Integer part: %d, Fractional part: %d\n", result.integer_part, result.fractional_part);
    return 0;
}