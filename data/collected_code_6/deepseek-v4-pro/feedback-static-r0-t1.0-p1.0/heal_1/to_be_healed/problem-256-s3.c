#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int count_primes(int n) {
    if (n <= 2) return 0;
    
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    bool *is_prime = (bool*)malloc(n * sizeof(bool));
    if (is_prime == NULL) return -1;
    
    for (int i = 2; i < n; i++) {
        is_prime[i] = true;
    }
    
    for (int i = 2; i * i < n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) count++;
    }
    
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(is_prime);
    return count;
}

int main() {
    printf("%d\n", count_primes(10));
    printf("%d\n", count_primes(0));
    printf("%d\n", count_primes(1));
    printf("%d\n", count_primes(2));
    printf("%d\n", count_primes(100));
    
    return 0;
}