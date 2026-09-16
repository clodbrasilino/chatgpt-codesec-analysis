#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t count_binary_sequences(int n)
{
    if (n <= 0)
    {
        return 0;
    }

    uint64_t *coefficients = calloc((size_t)n + 1, sizeof(uint64_t));
    if (coefficients == NULL)
    {
        return 0;
    }

    uint64_t *new_coefficients = calloc((size_t)n + 1, sizeof(uint64_t));
    if (new_coefficients == NULL)
    {
        free(coefficients);
        return 0;
    }

    coefficients[0] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i + 1; j++)
        {
            uint64_t value = 0;
            if (j <= i)
            {
                value = coefficients[j];
            }
            if (j > 0)
            {
                value += coefficients[j - 1];
            }
            new_coefficients[j] = value;
        }

        uint64_t *temp = coefficients;
        coefficients = new_coefficients;
        new_coefficients = temp;
    }

    uint64_t total = 0;
    for (int k = 0; k <= n; k++)
    {
        total += coefficients[k] * coefficients[k];
    }

    free(coefficients);
    free(new_coefficients);

    return total;
}

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = count_binary_sequences(n);
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}