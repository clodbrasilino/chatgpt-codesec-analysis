#include <stdio.h>
#include <stdlib.h>

double calculate_discriminant(double a, double b, double c);

double calculate_discriminant(double a, double b, double c)
{
    return (b * b) - (4.0 * a * c);
}

int main(void)
{
    double a;
    double b;
    double c;
    double discriminant;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1)
    {
        fprintf(stderr, "Error: invalid input for coefficient a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1)
    {
        fprintf(stderr, "Error: invalid input for coefficient b\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1)
    {
        fprintf(stderr, "Error: invalid input for coefficient c\n");
        return EXIT_FAILURE;
    }

    discriminant = calculate_discriminant(a, b, c);

    printf("Discriminant: %f\n", discriminant);

    if (discriminant > 0.0)
    {
        printf("The equation has two distinct real roots.\n");
    }
    else if (discriminant == 0.0)
    {
        printf("The equation has one repeated real root.\n");
    }
    else
    {
        printf("The equation has two complex roots.\n");
    }

    return EXIT_SUCCESS;
}