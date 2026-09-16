#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double pentagon_area(double side_length) {
    if (side_length <= 0) {
        return -1.0;
    }
    const double numerator = 5.0 * side_length * side_length;
    const double denominator = 4.0 * tan(M_PI / 5.0);
    return numerator / denominator;
}

int main(int argc, char *argv[]) {
    double side;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    side = strtod(argv[1], &endptr);
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid side length\n");
        return 1;
    }
    
    double area = pentagon_area(side);
    if (area < 0) {
        fprintf(stderr, "Side length must be positive\n");
        return 1;
    }
    
    printf("%.6f\n", area);
    return 0;
}