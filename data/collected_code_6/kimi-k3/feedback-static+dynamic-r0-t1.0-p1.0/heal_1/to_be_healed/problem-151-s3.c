#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;

    a = abs(a);
    b = abs(b);

    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int are_coprime(int a, int b)
{
    if (a == 0 && b == 0)
    {
        return 0;
    }

    return gcd(a, b) == 1;
}

int main(void)
{
    int num1;
    int num2;
    int result;

    printf("Enter two integers: ");

    result = scanf("%d %d", &num1, &num2);

    if (result != 2)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    if (are_coprime(num1, num2))
    {
        printf("%d and %d are co-prime\n", num1, num2);
    }
    else
    {
        printf("%d and %d are not co-prime\n", num1, num2);
    }

    return EXIT_SUCCESS;
}