#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    long max_div_6 = LONG_MAX / 6;
    /* Possible weaknesses found:
     *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     */
    if (n > (long)((sqrt(8 * max_div_6 + 1) - 1) / 2)) {
        fprintf(stderr, "Input too large, would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    long result = nth_tetrahedral_number(n);
    printf("The %ldth tetrahedral number is: %ld\n", n, result);
    return 0;
}