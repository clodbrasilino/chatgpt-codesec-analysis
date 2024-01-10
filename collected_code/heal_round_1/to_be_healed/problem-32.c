#include<stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

int largestPrimeFactor(int number) {
    int i;
    int largestPrime = -1;

    while (number % 2 == 0) {
        largestPrime = 2;
        number /= 2;
    }

    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'sqrt'
     */
    for (i = 3; i <= sqrt(number); i += 2) {
        while (number % i == 0) {
            largestPrime = i;
            number /= i;
        }
    }

    if (number > 2) {
        largestPrime = number;
    }

    return largestPrime;
}

int main() {
    int number;
    printf("Enter a positive integer: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);
    printf("The largest prime factor of %d is: %d", number, largestPrimeFactor(number));
    return 0;
}