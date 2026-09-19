#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 217, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

long long centered_hexagonal(int n) {
    if (n < 1) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    
    n = atoi(argv[1]);
    
    long long result = centered_hexagonal(n);
    
    if (result < 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}