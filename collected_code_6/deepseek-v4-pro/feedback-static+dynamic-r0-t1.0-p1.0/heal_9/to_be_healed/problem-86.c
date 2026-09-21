#include <stdio.h>
#include <stdlib.h>

long long centered_hexagonal(int n) {
    if (n < 1) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);
    
    long long result = centered_hexagonal(n);
    
    if (result < 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}