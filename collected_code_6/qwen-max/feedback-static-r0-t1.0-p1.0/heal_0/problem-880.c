#include <stdio.h>
#include <math.h>

int find_number_of_solutions(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        return 2;
    } else if (discriminant == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    double a, b, c;
    printf("Enter the coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 || a == 0) {
        printf("Invalid input.\n");
        return 1;
    }
    int solutions = find_number_of_solutions(a, b, c);
    printf("Number of solutions: %d\n", solutions);
    return 0;
}