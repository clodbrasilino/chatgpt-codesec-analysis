#include <stdio.h>
#include <limits.h>

int find_closest_smaller(int n, int *result)
{
    if (result == NULL)
    {
        return 0;
    }

    if (n == INT_MIN)
    {
        return 0;
    }

    *result = n - 1;
    return 1;
}

int main(void)
{
    int n;
    int result;
    int status;

    printf("Enter an integer: ");
    status = scanf("%d", &n);

    if (status != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (find_closest_smaller(n, &result))
    {
        printf("The closest smaller number than %d is %d\n", n, result);
    }
    else
    {
        fprintf(stderr, "No smaller number exists for %d\n", n);
        return 1;
    }

    return 0;
}