#include <stdio.h>

// Function to calculate factorial
int factorial(int n)
{
    int fact = 1;
    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }
    return fact;
}

// Function to calculate nCr mod p
int nCr_mod_p(int n, int r, int p)
{
    if (r > n)
    {
        return 0;
    }

    int numerator = factorial(n);
    int denominator = (factorial(r) * factorial(n - r)) % p;

    int power = p - 2;
    int result = 1;

    while (power > 0)
    {
        if (power % 2 == 1)
        {
            result = (result * denominator) % p;
        }
        denominator = (denominator * denominator) % p;
        power /= 2;
    }

    result = (result * numerator) % p;

    return result;
}

int main()
{
    int n = 5;
    int r = 2;
    int p = 1000000007;

    int nCr = nCr_mod_p(n, r, p);

    printf("Value of nCr mod p is: %d\n", nCr);

    return 0;
}