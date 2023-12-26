#include <stdio.h>

int countSolutions(float a, float b, float c) {
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        return 2;
    } else if (discriminant == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    float a = 0.0, b = 0.0, c = 0.0;

    printf("Enter the coefficients of the quadratic equation: ");
    int result = scanf("%f %f %f", &a, &b, &c);

    if(result == 3) {
        int solutions = countSolutions(a, b, c);
        printf("Number of solutions: %d", solutions);

        return 0;
    } else {
        printf("Invalid Input");
        return 1;
    }
}