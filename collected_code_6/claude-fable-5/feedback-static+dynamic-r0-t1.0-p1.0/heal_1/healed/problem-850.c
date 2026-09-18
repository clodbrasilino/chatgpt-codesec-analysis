#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(int angle_a, int angle_b, int angle_c)
{
    if (angle_a <= 0 || angle_b <= 0 || angle_c <= 0)
    {
        return 0;
    }

    if (angle_a >= 180 || angle_b >= 180 || angle_c >= 180)
    {
        return 0;
    }

    if ((long long)angle_a + (long long)angle_b + (long long)angle_c != 180LL)
    {
        return 0;
    }

    return 1;
}

int main(void)
{
    int angle_a = 0;
    int angle_b = 0;
    int angle_c = 0;
    int scanned = 0;

    printf("Enter three angles: ");

    scanned = scanf("%d %d %d", &angle_a, &angle_b, &angle_c);
    if (scanned != 3)
    {
        fprintf(stderr, "Error: invalid input. Please enter three integers.\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(angle_a, angle_b, angle_c))
    {
        printf("A triangle with positive area is possible.\n");
    }
    else
    {
        printf("A triangle with positive area is not possible.\n");
    }

    return EXIT_SUCCESS;
}