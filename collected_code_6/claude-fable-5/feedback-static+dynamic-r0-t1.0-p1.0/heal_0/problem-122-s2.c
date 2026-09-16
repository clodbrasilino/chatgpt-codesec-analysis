#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 100000

static int nth_smart_number(int n)
{
    int *factor_count;
    int i;
    int j;
    int found;
    int result;

    if (n <= 0) {
        return -1;
    }

    factor_count = calloc((size_t)MAX_LIMIT, sizeof *factor_count);
    if (factor_count == NULL) {
        return -1;
    }

    found = 0;
    result = -1;

    for (i = 2; i < MAX_LIMIT; i++) {
        if (factor_count[i] == 0) {
            for (j = i; j < MAX_LIMIT; j += i) {
                factor_count[j]++;
            }
        }
        if (factor_count[i] >= 3) {
            found++;
            if (found == n) {
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
    int answer;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    answer = nth_smart_number(n);
    if (answer < 0) {
        fprintf(stderr, "Could not compute the %d'th smart number\n", n);
        return EXIT_FAILURE;
    }

    printf("The %d'th smart number is %d\n", n, answer);
    return EXIT_SUCCESS;
}