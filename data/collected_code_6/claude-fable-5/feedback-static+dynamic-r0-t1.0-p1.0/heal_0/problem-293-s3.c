#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double find_third_side(double side_a, double side_b, int find_hypotenuse, int *error);

double find_third_side(double side_a, double side_b, int find_hypotenuse, int *error)
{
    double result = 0.0;

    if (error == NULL) {
        return 0.0;
    }

    *error = 0;

    if (side_a <= 0.0 || side_b <= 0.0) {
        *error = 1;
        return 0.0;
    }

    if (find_hypotenuse != 0) {
        result = sqrt((side_a * side_a) + (side_b * side_b));
    } else {
        if (side_b <= side_a) {
            *error = 1;
            return 0.0;
        }
        result = sqrt((side_b * side_b) - (side_a * side_a));
    }

    if (!isfinite(result)) {
        *error = 1;
        return 0.0;
    }

    return result;
}

int main(void)
{
    double side_a = 0.0;
    double side_b = 0.0;
    int choice = 0;
    int error = 0;
    double third_side = 0.0;

    printf("Choose calculation mode:\n");
    printf("1 - Find hypotenuse (given two legs)\n");
    printf("2 - Find missing leg (given one leg and hypotenuse)\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input for choice.\n");
        return EXIT_FAILURE;
    }

    if (choice != 1 && choice != 2) {
        fprintf(stderr, "Choice must be 1 or 2.\n");
        return EXIT_FAILURE;
    }

    if (choice == 1) {
        printf("Enter first leg: ");
        if (scanf("%lf", &side_a) != 1) {
            fprintf(stderr, "Invalid input for first leg.\n");
            return EXIT_FAILURE;
        }
        printf("Enter second leg: ");
        if (scanf("%lf", &side_b) != 1) {
            fprintf(stderr, "Invalid input for second leg.\n");
            return EXIT_FAILURE;
        }
        third_side = find_third_side(side_a, side_b, 1, &error);
    } else {
        printf("Enter known leg: ");
        if (scanf("%lf", &side_a) != 1) {
            fprintf(stderr, "Invalid input for leg.\n");
            return EXIT_FAILURE;
        }
        printf("Enter hypotenuse: ");
        if (scanf("%lf", &side_b) != 1) {
            fprintf(stderr, "Invalid input for hypotenuse.\n");
            return EXIT_FAILURE;
        }
        third_side = find_third_side(side_a, side_b, 0, &error);
    }

    if (error != 0) {
        fprintf(stderr, "Invalid triangle dimensions provided.\n");
        return EXIT_FAILURE;
    }

    printf("The third side is: %f\n", third_side);

    return EXIT_SUCCESS;
}