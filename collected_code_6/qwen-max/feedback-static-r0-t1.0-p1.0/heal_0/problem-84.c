#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n, int *sequence) {
    if (n == 1 || n == 2) {
        return 1;
    }
    if (sequence[n] != 0) {
        return sequence[n];
    }
    sequence[n] = newman_conway(newman_conway(n-1, sequence), sequence) + newman_conway(n - newman_conway(n-1, sequence), sequence);
    return sequence[n];
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    int *sequence = (int *)malloc((n + 1) * sizeof(int));
    if (sequence == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 1; i <= n; ++i) {
        sequence[i] = 0;
    }

    sequence[1] = 1;

    printf("The %d-th number in the Newman-Conway sequence is: %d\n", n, newman_conway(n, sequence));

    free(sequence);
    return 0;
}