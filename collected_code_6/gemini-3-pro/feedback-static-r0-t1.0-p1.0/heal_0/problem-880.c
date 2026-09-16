#include <stdio.h>
#include <stdlib.h>

int find_number_of_solutions(double a, double b, double c) {
    if (a == 0.0) {
        if (b == 0.0) {
            if (c == 0.0) {
                return -1; 
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0.0) {
        return 2;
    } else if (discriminant == 0.0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    double a, b, c;
    int solutions;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    solutions = find_number_of_solutions(a, b, c);

    if (solutions == -1) {
        printf("Infinite solutions\n");
    } else {
        printf("%d\n", solutions);
    }

    return EXIT_SUCCESS;
}