#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const char *tuple) {
    double result;
    if (sscanf(tuple, "(%lf)", &result) != 1) {
        fprintf(stderr, "Error: Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main() {
    const char *input = "(3.14)";
    double output = tuple_to_float(input);
    printf("Converted float: %f\n", output);
    return 0;
}