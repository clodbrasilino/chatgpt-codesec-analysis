#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

void find_multiples(int n, int m, int *multiples) {
    if (multiples == NULL || n <= 0 || m <= 0) {
        return;
    }
    
    for (int i = 0; i < m; i++) {
        multiples[i] = n * (i + 1);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr_n, *endptr_m;
    long n_long = strtol(argv[1], &endptr_n, 10);
    long m_long = strtol(argv[2], &endptr_m, 10);
    
    if (*endptr_n != '\0' || *endptr_m != '\0' ||
        n_long <= 0 || m_long <= 0 || 
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        n_long > INT_MAX || m_long > INT_MAX) {
        fprintf(stderr, "Both arguments must be positive integers\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)n_long;
    int m = (int)m_long;
    
    int *multiples = (int *)malloc((size_t)m * sizeof(int));
    if (multiples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    find_multiples(n, m, multiples);
    
    for (int i = 0; i < m; i++) {
        printf("%d ", multiples[i]);
    }
    printf("\n");
    
    free(multiples);
    
    return EXIT_SUCCESS;
}