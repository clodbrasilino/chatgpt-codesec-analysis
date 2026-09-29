#include <stdio.h>
#include <stdlib.h>

int find_directrix(double a, double b, double c, double *directrix)
{
    if (directrix == NULL) {
        return -1;
    }
    if (a == 0.0) {
        return -1;
    }
    *directrix = c - ((b * b) + 1.0) / (4.0 * a);
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    double directrix;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1) {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    if (find_directrix(a, b, c, &directrix) != 0) {
        fprintf(stderr, "Error: coefficient a must be non-zero\n");
        return EXIT_FAILURE;
    }

    printf("Directrix: y = %f\n", directrix);
    return EXIT_SUCCESS;
}