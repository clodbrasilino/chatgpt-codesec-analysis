#include <stdio.h>
#include <stdlib.h>

int isTriangleValid(int a, int b, int c);

int isTriangleValid(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return 0;
    }

    if ((a + b + c) == 180)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    int a;
    int b;
    int c;
    int result;

    printf("Enter three angles: ");

    if (scanf("%d %d %d", &a, &b, &c) != 3)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = isTriangleValid(a, b, c);

    if (result == 1)
    {
        printf("A triangle with positive area is possible.\n");
    }
    else
    {
        printf("A triangle with positive area is not possible.\n");
    }

    return EXIT_SUCCESS;
}