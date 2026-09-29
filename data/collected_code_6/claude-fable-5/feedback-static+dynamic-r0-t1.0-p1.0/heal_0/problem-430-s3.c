#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int find_directrix(double a, double b, double c, double *directrix)
{
    if (directrix == NULL)
    {
        return -1;
    }

    if (fabs(a) < 1e-12)
    {
        return -1;
    }

    *directrix = c - ((b * b) + 1.0) / (4.0 * a);

    return 0;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double directrix = 0.0;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1)
    {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1)
    {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1)
    {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    if (find_directrix(a, b, c, &directrix) != 0)
    {
        fprintf(stderr, "Error: coefficient a must be non-zero\n");
        return EXIT_FAILURE;
    }

    printf("Directrix: y = %.6f\n", directrix);

    return EXIT_SUCCESS;
}