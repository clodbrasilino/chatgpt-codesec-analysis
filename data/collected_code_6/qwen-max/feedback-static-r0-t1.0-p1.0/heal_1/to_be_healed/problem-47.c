#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

int last_digit_factorial_division(long a, long b) {
    long i;
    /* Possible weaknesses found:
     *  Variable 'prod' is assigned a value that is never used. [unreadVariable]
     */
    int prod = 1, fact_a = 1, fact_b = 1;

    for (i = 2; i <= b; i++) {
        fact_b = (fact_b * i) % 10;
        if (i <= a) {
            fact_a = (fact_a * i) % 10;
        }
    }

    int result = 1;
    for (i = 0; i < b - a; i++) {
        result = (result * fact_a) % 10;
    }

    /* Possible weaknesses found:
     *  invalid operands to binary expression ('double' and 'int')
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     *  invalid operands to binary % (have 'double' and 'int')
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return (fact_b * pow(result, 10 - 2)) % 10;
}

int main() {
    long a, b;
    scanf("%ld %ld", &a, &b);

    if (a < 0 || b < 0 || a > b) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int last_digit = last_digit_factorial_division(a, b);
    printf("%d\n", last_digit);

    return EXIT_SUCCESS;
}