#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    
    int *sequence = (int *)malloc((n + 1) * sizeof(int));
    if (sequence == NULL) {
        return -1;
    }
    
    sequence[1] = 1;
    sequence[2] = 1;
    
    for (int i = 3; i <= n; i++) {
        sequence[i] = sequence[sequence[i - 1]] + sequence[i - sequence[i - 1]];
    }
    
    int result = sequence[n];
    free(sequence);
    return result;
}

int main(void) {
    int n;
    printf("Enter the position (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = newman_conway(n);
    if (result == -1) {
        fprintf(stderr, "Invalid input or memory allocation failed\n");
        return 1;
    }
    
    printf("The %d-th number in Newman-Conway sequence is: %d\n", n, result);
    return 0;
}