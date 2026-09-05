#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_nth_term(int first_term, int common_difference, int n, int *result)
{
    if (result == NULL || n < 1)
    {
        return -1;
    }

    long long calculation = (long long)first_term + 
                           ((long long)(n - 1) * (long long)common_difference);

    if (calculation > INT_MAX || calculation < INT_MIN)
    {
        return -1;
    }

    *result = (int)calculation;
    return 0;
}

int main(void)
{
    int first_term;
    int common_difference;
    int n;
    int result;
    int status;

    printf("Enter first term, common difference, and n: ");
    
    if (scanf("%d %d %d", &first_term, &common_difference, &n) != 3)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    status = find_nth_term(first_term, common_difference, n, &result);
    
    if (status != 0)
    {
        fprintf(stderr, "Error: Invalid parameters or integer overflow\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th term is: %d\n", n, result);
    
    return EXIT_SUCCESS;
}