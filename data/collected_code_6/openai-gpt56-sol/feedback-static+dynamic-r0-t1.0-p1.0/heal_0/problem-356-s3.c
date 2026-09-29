#include <stdio.h>
#include <stdlib.h>

static int find_third_angle(int first_angle, int second_angle, int *third_angle)
{
    if (third_angle == NULL ||
        first_angle <= 0 ||
        second_angle <= 0 ||
        first_angle >= 180 ||
        second_angle >= 180 ||
        first_angle + second_angle >= 180) {
        return 0;
    }

    *third_angle = 180 - first_angle - second_angle;
    return 1;
}

int main(void)
{
    int first_angle;
    int second_angle;
    int third_angle;

    if (scanf("%d %d", &first_angle, &second_angle) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_third_angle(first_angle, second_angle, &third_angle)) {
        fputs("Invalid triangle angles\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", third_angle);
    return EXIT_SUCCESS;
}