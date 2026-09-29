#include <stdio.h>
#include <stdlib.h>

#define MAX_LUCAS_INDEX 90

static long long lucas(int n)
{
    long long a = 2;
    long long b = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    long long temp;
    int i;

    if (n == 0)
    {
        return a;
    }
    if (n == 1)
    {
        return b;
    }

    for (i = 2; i <= n; i++)
    {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}

int main(void)
{
    int n;
    int result;

    printf("Enter n: ");
    result = scanf("%d", &n);

    if (result != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0)
    {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (n > MAX_LUCAS_INDEX)
    {
        fprintf(stderr, "Error: n must not exceed %d to avoid overflow\n", MAX_LUCAS_INDEX);
        return EXIT_FAILURE;
    }

    printf("Lucas number %d is %lld\n", n, lucas(n));

    return EXIT_SUCCESS;
}