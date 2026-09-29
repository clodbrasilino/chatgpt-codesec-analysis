#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares_of_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1468588942 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:8999,execs:4659,op:havoc,rep:1)
     * UBSan: signed integer overflow: 7547957620302330 * 122865437 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:7197,execs:3711,op:havoc,rep:1)
     * UBSan: signed integer overflow: -1994034517496471046 * -1357789411 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:8999,execs:4659,op:havoc,rep:1)
     */
    return (long long)n * (2 * n - 1) * (2 * n + 1) / 3;
}

int main(void) {
    int n;
    char input[32];
    char *endptr;
    
    printf("Enter a positive integer n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    n = (int)strtol(input, &endptr, 10);
    
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of squares of first %d odd natural numbers: %lld\n", 
           n, sum_of_squares_of_odd_numbers(n));
    
    return EXIT_SUCCESS;
}