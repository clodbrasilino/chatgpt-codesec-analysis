#include <stdio.h>
#include <stdlib.h>

long long pell_number(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    long long prev2 = 0;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:391,execs:218,op:havoc,rep:2)
         * UBSan: signed integer overflow: 5052016396815640554 + 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:391,execs:218,op:havoc,rep:2)
         */
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    
    printf("Enter n to calculate nth Pell number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = pell_number(n);
    
    if (result == -1 && n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("Pell number P%d = %lld\n", n, result);
    
    return EXIT_SUCCESS;
}