#include <stdio.h>

int min(int a, int b);

int main(void)
{
    int num1;
    int num2;
    int result;

    printf("Enter two integers: ");
    if (scanf("%d %d", &num1, &num2) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = min(num1, num2);
    printf("Minimum: %d\n", result);

    return 0;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}