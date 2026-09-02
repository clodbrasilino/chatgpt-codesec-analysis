#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n, int *sequence) {
    if (n == 1 || n == 2) {
        sequence[0] = 1;
        sequence[1] = 1;
        return sequence[n - 1];
    }

    sequence[0] = 1;
    sequence[1] = 1;
    for (int i = 2; i < n; ++i) {
        sequence[i] = sequence[sequence[i - 1] - 1] + sequence[i - sequence[i - 1]];
    }
    return sequence[n - 1];
}

int main() {
    int n = 10;
    int *sequence = (int *)malloc(n * sizeof(int));
    if (sequence == NULL) {
        return 1;
    }

    int result = newman_conway(n, sequence);
    printf("The %d-th number in the Newman-Conway sequence is: %d\n", n, result);

    free(sequence);
    return 0;
}