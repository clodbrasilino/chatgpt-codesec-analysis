#include <stdio.h>
#include <stdlib.h>

double maxAveragePath(int n, const int *matrix)
{
    if (n <= 0 || matrix == NULL)
        return 0.0;

    long long *prev = malloc((size_t)n * sizeof(*prev));
    long long *curr = malloc((size_t)n * sizeof(*curr));

    if (prev == NULL || curr == NULL)
    {
        free(prev);
        free(curr);
        return 0.0;
    }

    prev[0] = matrix[0];
    for (int j = 1; j < n; ++j)
    {
        prev[j] = prev[j - 1] + matrix[(size_t)j];
    }

    for (int i = 1; i < n; ++i)
    {
        curr[0] = prev[0] + matrix[(size_t)i * (size_t)n];

        for (int j = 1; j < n; ++j)
        {
            long long left = curr[j - 1];
            long long up = prev[j];
            curr[j] = (left > up ? left : up) + matrix[(size_t)i * (size_t)n + (size_t)j];
        }

        long long *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    long long max_sum = prev[n - 1];

    free(prev);
    free(curr);

    return (double)max_sum / (double)(2LL * n - 1);
}

int main(void)
{
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("%.6f\n", maxAveragePath(3, &matrix[0][0]));

    return 0;
}