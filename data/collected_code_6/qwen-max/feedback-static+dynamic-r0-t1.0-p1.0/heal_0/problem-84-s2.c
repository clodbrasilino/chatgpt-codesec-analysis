#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n, int *cache) {
    if (n == 1 || n == 2) return 1;
    if (cache[n] != 0) return cache[n];
    cache[n] = newman_conway(newman_conway(n - 1, cache), cache) + newman_conway(n - newman_conway(n - 1, cache), cache);
    return cache[n];
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int *cache = (int *)malloc((n + 1) * sizeof(int));
    if (cache == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i <= n; i++) {
        cache[i] = 0;
    }

    int result = newman_conway(n, cache);

    free(cache);
    printf("The %d-th number in the Newman-Conway sequence is: %d\n", n, result);

    return 0;
}