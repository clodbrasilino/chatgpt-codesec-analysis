#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    if (n <= 2) {
        return 1;
    }

    int *seq = (int *)malloc((n + 1) * sizeof(int));
    if (seq == NULL) {
        exit(EXIT_FAILURE);
    }

    seq[0] = 0;
    seq[1] = 1;
    seq[2] = 1;

    for (int i = 3; i <= n; i++) {
        seq[i] = seq[seq[i - 1]] + seq[i - seq[i - 1]];
    }

    int result = seq[n];
    free(seq);

    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    int result = newman_conway(n);
    printf("%d\n", result);

    return 0;
}