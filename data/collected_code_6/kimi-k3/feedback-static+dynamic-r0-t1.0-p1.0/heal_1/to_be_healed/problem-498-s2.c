#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main(void)
{
    int a, b;
    int result;

    if (scanf("%d %d", &a, &b) != 2)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (a <= 0 || b <= 0)
    {
        fprintf(stderr, "Numbers must be positive\n");
        return EXIT_FAILURE;
    }

    result = gcd(a, b);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}

int gcd(int a, int b)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;

    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}