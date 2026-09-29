#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n, int *cache) {
    if (n == 1 || n == 2) return 1;
    if (cache[n] != 0) return cache[n];
    int a = newman_conway(n - 1, cache);
    int b = newman_conway(n - a, cache);
    cache[n] = a + b;
    return cache[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:5520,execs:167,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int *cache = (int *)malloc((size_t)(n + 1) * sizeof(int));
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