#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int are_roots_equal_opposite(double a, double b, double c) {
    /* Possible weaknesses found:
     *  Assuming condition 'fabs(a)<1e-12' is false
     */
    if (fabs(a) < 1e-12) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Condition 'fabs(a)>=1e-12' is always true [knownConditionTrueFalse]
     *  Condition 'fabs(a)>=1e-12' is always true
     */
    if (fabs(b) < 1e-12 && fabs(a) >= 1e-12) {
        if (fabs(c) < 1e-12) {
            return 1;
        }
        double discriminant = b * b - 4.0 * a * c;
        if (discriminant < 0.0) {
            return 0;
        }
        return 0;
    }
    if (fabs(b) < 1e-12) {
        return 0;
    }
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return 0;
    }
    double root1 = (-b + sqrt(discriminant)) / (2.0 * a);
    double root2 = (-b - sqrt(discriminant)) / (2.0 * a);
    double sum = root1 + root2;
    double magnitude = fmax(fabs(root1), fabs(root2));
    if (magnitude < 1e-12) {
        return 1;
    }
    if (fabs(sum) / magnitude < 1e-9) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    double c = strtod(argv[3], NULL);
    if (fabs(a) < 1e-12) {
        return EXIT_FAILURE;
    }
    int result = are_roots_equal_opposite(a, b, c);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}