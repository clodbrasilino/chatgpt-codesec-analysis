#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int angle1, int angle2, int angle3)
{
    if (angle1 <= 0 || angle2 <= 0 || angle3 <= 0)
    {
        return false;
    }

    if (angle1 + angle2 + angle3 != 180)
    {
        return false;
    }

    return true;
}

int main(void)
{
    int a;
    int b;
    int c;

    printf("Enter three angles: ");

    if (scanf("%d %d %d", &a, &b, &c) != 3)
    {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    if (is_valid_triangle(a, b, c))
    {
        printf("A triangle with positive area is possible.\n");
    }
    else
    {
        printf("A triangle with positive area is not possible.\n");
    }

    return 0;
}