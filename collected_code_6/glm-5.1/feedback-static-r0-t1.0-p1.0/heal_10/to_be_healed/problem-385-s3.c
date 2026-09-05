#include <stdio.h>
#include <stdlib.h>

unsigned long perrin(int n) {
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'MAX_N' undeclared (first use in this function)
     *  use of undeclared identifier 'MAX_N'
     */
    unsigned long p[MAX_N];
    p[0] = 3;
    p[1] = 0;
    p[2] = 2;
    for (int i = 3; i <= n; i++) {
        p[i] = p[i - 2] + p[i - 3];
    }
    return p[n];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > 35) {
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    unsigned long result = perrin(n);
    printf("%lu\n", result);
    
    return EXIT_SUCCESS;
}