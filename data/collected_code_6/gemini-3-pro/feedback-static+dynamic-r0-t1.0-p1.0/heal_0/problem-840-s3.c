#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkRootsEqualAndOpposite(double a, double b, double c) {
    if (a == 0.0) {
        return false;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0) {
        return false;
    }

    if (b == 0.0 && c != 0.0 && (a * c) < 0.0) {
        return true;
    }

    return false;
}

int main() {
    double a = 0;
    double b = 0;
    double c = 0;

    int result = scanf("%lf %lf %lf", &a, &b, &c);
    
    if (result != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (a == 0.0) {
        fprintf(stderr, "Coefficient 'a' cannot be zero for a quadratic equation.\n");
        return EXIT_FAILURE;
    }

    bool areEqualAndOpposite = checkRootsEqualAndOpposite(a, b, c);

    if (areEqualAndOpposite) {
        printf("The roots are numerically equal but opposite in sign.\n");
    } else {
        printf("The roots are NOT numerically equal but opposite in sign.\n");
    }

    return EXIT_SUCCESS;
}