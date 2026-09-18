#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int round_to_multiple(int number, int multiple, int *result)
{
    if (result == NULL)
    {
        return -1;
    }
    
    if (multiple == 0)
    {
        return -1;
    }
    
    long long n = (long long)number;
    long long m = (long long)multiple;
    long long half = m / 2;
    long long res;
    
    if (n > 0)
    {
        res = ((n + half) / m) * m;
    }
    else
    {
        res = ((n - half) / m) * m;
    }
    
    if (res > INT_MAX || res < INT_MIN)
    {
        return -1;
    }
    
    *result = (int)res;
    return 0;
}

int main(void)
{
    int number = 0;
    int multiple = 0;
    int result = 0;
    int status = 0;
    
    printf("Enter number: ");
    if (scanf("%d", &number) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter multiple: ");
    if (scanf("%d", &multiple) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    status = round_to_multiple(number, multiple, &result);
    if (status != 0)
    {
        fprintf(stderr, "Error: invalid multiple or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %d\n", result);
    
    return EXIT_SUCCESS;
}