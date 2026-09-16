#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int last_digit_factorial_division(long a, long b) {
    long i;
    int fact_a = 1, fact_b = 1;

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
     *  invalid operands to binary % (have 'double' and 'int')
     *  invalid operands to binary expression ('double' and 'int')
     */
    return (int)((fact_b * pow(result, 10 - 2)) % 10);
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