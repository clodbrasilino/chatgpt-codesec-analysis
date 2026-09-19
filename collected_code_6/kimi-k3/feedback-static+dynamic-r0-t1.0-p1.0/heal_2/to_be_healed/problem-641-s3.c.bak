#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long nonagonal_number(int n) {
    if (n < 0) {
        return -1;
    }
    
    if (n > 1518500249) {
        errno = ERANGE;
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1211111111 * 8477777772 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000008,time:54638,execs:23482,op:havoc,rep:2)
     * UBSan: signed integer overflow: 1199999999 * 8399999988 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:5280,execs:2349,op:havoc,rep:12)
     */
    return (long long)n * (7LL * n - 5) / 2;
}

int main(void) {
    int n;
    char buffer[256];
    char *endptr;
    long val;

    printf("Enter the value of n: ");
    
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
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    
    long long result = nonagonal_number(n);
    if (result == -1 && errno == ERANGE) {
        fprintf(stderr, "Error: result would overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Nonagonal number for n=%d is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}