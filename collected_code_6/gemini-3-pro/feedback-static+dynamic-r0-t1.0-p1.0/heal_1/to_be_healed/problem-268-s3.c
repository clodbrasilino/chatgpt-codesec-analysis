#include <stdio.h>
#include <stdlib.h>

long long int find_star_number(int n) {
    if (n <= 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8968628904 * 1494771483 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:535,execs:269,op:havoc,rep:3)
     */
    return 6LL * n * (n - 1) + 1;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    long long int result = find_star_number(n);
    
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}