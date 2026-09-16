#include <stdio.h>
#include <stdlib.h>

double find_third_angle(double angle1, double angle2)
{
    return 180.0 - (angle1 + angle2);
}

int is_valid_angle_pair(double angle1, double angle2)
{
    if (angle1 <= 0.0 || angle2 <= 0.0) {
        return 0;
    }
    if ((angle1 + angle2) >= 180.0) {
        return 0;
    }
    return 1;
}

int main(void)
{
    double angle1 = 0.0;
    double angle2 = 0.0;
    double angle3 = 0.0;

    printf("Enter the first angle: ");
    if (scanf("%lf", &angle1) != 1) {
        fprintf(stderr, "Error: invalid input for first angle.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second angle: ");
    if (scanf("%lf", &angle2) != 1) {
        fprintf(stderr, "Error: invalid input for second angle.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_angle_pair(angle1, angle2)) {
        fprintf(stderr, "Error: angles must be positive and their sum must be less than 180 degrees.\n");
        return EXIT_FAILURE;
    }

    angle3 = find_third_angle(angle1, angle2);

    printf("The third angle is: %.2f degrees\n", angle3);

    return EXIT_SUCCESS;
}