#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

long long int sumOfFifthPowers(int n) {
    long long int sum = 0;
    
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         *  include '<math.h>' or provide a declaration of 'pow'
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'pow' [-Wbuiltin-declaration-mismatch]
         */
        sum += (long long int)pow(i, 5);
    }
    
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    long long int result = sumOfFifthPowers(n);
    
    printf("Sum of fifth powers of %d natural numbers = %lld", n, result);
    
    return 0;
}