#include <stdio.h>
#include <stdlib.h>

unsigned long int catalanDP(unsigned int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    unsigned long int *catalan = (unsigned long int *)malloc((n + 1) * sizeof(unsigned long int));
    if (catalan == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    catalan[0] = 1;
    catalan[1] = 1;

    for (unsigned int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (unsigned int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }

    unsigned long int result = catalan[n];
    free(catalan);

    return result;
}

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 19) {
        fprintf(stderr, "Input too large, result will overflow\n");
        return EXIT_FAILURE;
    }

    unsigned long int result = catalanDP(n);
    printf("%lu\n", result);

    return EXIT_SUCCESS;
}