#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    /* Possible weaknesses found:
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     */
    int g = gcd(abs(a), abs(b));
    int sum = 0;
    int sqrt_g = (int)sqrt(g);
    
    for (int i = 1; i <= sqrt_g; i++) {
        if (g % i == 0) {
            sum += i;
            int other = g / i;
            if (other != i) {
                sum += other;
            }
        }
    }
    
    return sum;
}

int main(void) {
    int a, b;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (a == 0 && b == 0) {
        fprintf(stderr, "Both numbers cannot be zero\n");
        return 1;
    }
    
    int result = sum_common_divisors(a, b);
    printf("Sum of common divisors: %d\n", result);
    
    return 0;
}