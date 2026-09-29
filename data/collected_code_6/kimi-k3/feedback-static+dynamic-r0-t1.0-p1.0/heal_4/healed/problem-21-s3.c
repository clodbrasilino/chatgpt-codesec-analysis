#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int find_multiples(int n, int m, int **result)
{
    int *multiples = NULL;
    int i;

    if (m <= 0 || result == NULL)
    {
        return -1;
    }

    if ((size_t)m > SIZE_MAX / sizeof(int))
    {
        return -1;
    }

    multiples = (int *)malloc((size_t)m * sizeof(int));
    if (multiples == NULL)
    {
        return -1;
    }

    for (i = 0; i < m; i++)
    {
        if (n != 0)
        {
            if (n > 0 && (i + 1) > INT_MAX / n)
            {
                free(multiples);
                return -1;
            }
            if (n < 0 && (i + 1) < INT_MIN / n)
            {
                free(multiples);
                return -1;
            }
        }
        multiples[i] = n * (i + 1);
    }

    *result = multiples;
    return 0;
}

int main(void)
{
    int n, m;
    int *multiples = NULL;
    int i;

    if (printf("Enter the number (n): ") < 0)
    {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter the count of multiples (m): ") < 0)
    {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &m) != 1)
    {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }

    if (find_multiples(n, m, &multiples) != 0)
    {
        fprintf(stderr, "Error: Invalid parameters or memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("First %d multiples of %d: ", m, n);
    for (i = 0; i < m; i++)
    {
        printf("%d ", multiples[i]);
    }
    printf("\n");

    free(multiples);
    multiples = NULL;

    return EXIT_SUCCESS;
}