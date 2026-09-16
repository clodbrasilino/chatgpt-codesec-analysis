#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n)
{
    int *p;
    int i;
    int result;

    if (n <= 0) {
        return -1;
    }

    if (n <= 2) {
        return 1;
    }

    p = malloc((size_t)(n + 1) * sizeof(int));
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
    int result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = newman_conway(n);
    if (result < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("The %d-th Newman-Conway number is %d\n", n, result);
    return EXIT_SUCCESS;
}