#include <stdio.h>
#include <stdlib.h>

#define LIMIT 100000

static int smart_number(int n)
{
    int *factor_count;
    int i;
    int j;
    int count;
    int result;

    if (n < 1) {
        return -1;
    }

    factor_count = calloc((size_t)LIMIT, sizeof(int));
    if (factor_count == NULL) {
        return -1;
    }

    for (i = 2; i < LIMIT; i++) {
        if (factor_count[i] == 0) {
            for (j = i; j < LIMIT; j += i) {
                factor_count[j]++;
            }
        }
    }

    count = 0;
    result = -1;
    for (i = 2; i < LIMIT; i++) {
        if (factor_count[i] >= 3) {
            count++;
            if (count == n) {
                result = i;
                break;
            }
        }
    }

    free(factor_count);
    return result;
}

int main(void)
{
    int n;
    int result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = smart_number(n);
    if (result == -1) {
        fprintf(stderr, "Could not compute the %d'th smart number\n", n);
        return EXIT_FAILURE;
    }

    printf("The %d'th smart number is %d\n", n, result);
    return EXIT_SUCCESS;
}