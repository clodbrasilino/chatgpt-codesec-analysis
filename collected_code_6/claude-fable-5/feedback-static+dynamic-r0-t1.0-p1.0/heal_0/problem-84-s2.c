#include <stdio.h>
#include <stdlib.h>

static int newman_conway(int n)
{
    int *p;
    int i;
    int result;

    if (n < 1) {
        return -1;
    }

    if (n <= 2) {
        return 1;
    }

    p = malloc(((size_t)n + 1U) * sizeof(int));
    if (p == NULL) {
        return -1;
    }

    p[1] = 1;
    p[2] = 1;

    for (i = 3; i <= n; i++) {
        p[i] = p[p[i - 1]] + p[i - p[i - 1]];
    }

    result = p[n];
    free(p);

    return result;
}

int main(void)
{
    int n;
    int value;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    value = newman_conway(n);
    if (value < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th Newman-Conway number is %d\n", n, value);

    return EXIT_SUCCESS;
}