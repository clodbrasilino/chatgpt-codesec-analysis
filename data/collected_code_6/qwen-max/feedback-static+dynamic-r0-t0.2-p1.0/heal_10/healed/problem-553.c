#include <stdio.h>
#include <stdlib.h>

double tuple_to_float(const char *tuple) {
    double result;
    if (sscanf(tuple, "(%lf)", &result) != 1) {
        printf("Invalid input format\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int main() {
    const char *test_cases[] = {"(4.56)", "(7.256)", "(8.123)"};
    for (int i = 0; i < 3; i++) {
        double output = tuple_to_float(test_cases[i]);
        printf("%.3f\n", output);
    }
    return 0;
}