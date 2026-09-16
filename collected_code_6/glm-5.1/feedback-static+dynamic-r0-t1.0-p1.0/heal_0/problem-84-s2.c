#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    int *p = (int *)malloc((n + 1) * sizeof(int));
    if (p == NULL) {
        exit(EXIT_FAILURE);
    }
    p[1] = 1;
    p[2] = 1;
    for (int i = 3; i <= n; i++) {
        p[i] = p[p[i - 1]] + p[i - p[i - 1]];
    }
    int result = p[n];
    free(p);
    return result;
}

int main() {
    int n = 10;
    int result = newman_conway(n);
    printf("%d\n", result);
    return 0;
}