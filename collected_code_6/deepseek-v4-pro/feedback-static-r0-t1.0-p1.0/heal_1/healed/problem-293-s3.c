#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double find_third_side(double a, double b, double c) {
    if (a <= 0 && b <= 0)
        return -1.0;
    if (a <= 0)
        return sqrt(c * c - b * b);
    if (b <= 0)
        return sqrt(c * c - a * a);
    if (c <= 0)
        return sqrt(a * a + b * b);
    return -1.0;
}

int main(int argc, char *argv[]) {
    double a, b, c;
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side1> <side2> <side3>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    a = atof(argv[1]);
    b = atof(argv[2]);
    c = atof(argv[3]);
    
    double result = find_third_side(a, b, c);
    if (result < 0) {
        fprintf(stderr, "Invalid input: exactly one side must be zero or negative\n");
        return EXIT_FAILURE;
    }
    
    printf("%.2f\n", result);
    return EXIT_SUCCESS;
}