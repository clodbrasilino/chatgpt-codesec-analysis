#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const char *tuple) {
    double result;
    int n = sscanf(tuple, "(%lf)", &result);
    if (n != 1) {
        fprintf(stderr, "Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main() {
    const char *input = "(3.14)";
    double output = tuple_to_float(input);
    printf("%f\n", output);
    return 0;
}