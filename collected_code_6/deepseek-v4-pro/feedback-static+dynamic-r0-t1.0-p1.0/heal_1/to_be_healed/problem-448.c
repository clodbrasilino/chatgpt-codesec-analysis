#include <stdio.h>
#include <stdlib.h>

int perrin_sum(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 3;
    }
    if (n == 2) {
        return 5;
    }
    
    int *perrin = (int *)malloc((n + 1) * sizeof(int));
    if (perrin == NULL) {
        return -1;
    }
    
    perrin[0] = 3;
    perrin[1] = 0;
    perrin[2] = 2;
    
    int sum = 5;
    
    for (int i = 3; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1442968193 + 1089264462 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:350,execs:183,op:havoc,rep:14)
         */
        perrin[i] = perrin[i - 2] + perrin[i - 3];
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1911525875 + 620706778 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:350,execs:183,op:havoc,rep:14)
         */
        sum += perrin[i];
    }
    
    free(perrin);
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = perrin_sum(n);
    if (result == -1 && n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of Perrin numbers up to P(%d) = %d\n", n, result);
    
    return EXIT_SUCCESS;
}