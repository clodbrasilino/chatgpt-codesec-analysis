#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long cube_sum_even(int n) {
    long long sum = 0;
    long long i;
    
    for (i = 1; i <= n; i++) {
        long long even_num = 2 * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223013771341927200 + 796134035438568 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:869,execs:378,op:havoc,rep:4)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:869,execs:378,op:havoc,rep:4)
         */
        sum += even_num * even_num * even_num;
    }
    
    return sum;
}

int main(void) {
    char buffer[256];
    char *endptr;
    long val;
    int n;
    long long result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    result = cube_sum_even(n);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}