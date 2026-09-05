#include <stdio.h>

int isIsosceles(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
        return 0;
    if (a + b <= c || a + c <= b || b + c <= a)
        return 0;
    if (a == b || b == c || a == c)
        return 1;
    return 0;
}

int main(void)
{
    int a, b, c;
    printf("Enter three sides of the triangle: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3)
    {
        printf("Invalid input\n");
        return 1;
    }
    if (isIsosceles(a, b, c))
        printf("The triangle is isosceles\n");
    else
        printf("The triangle is not isosceles\n");
    return 0;
}