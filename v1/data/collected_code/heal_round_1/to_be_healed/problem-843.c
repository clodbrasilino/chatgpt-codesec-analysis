#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

// Function to find the nth super ugly number
int nthSuperUglyNumber(int n, int* primes, int k) {
    int* uglyNumbers = (int*) malloc(sizeof(int) * n);
    int* indices = (int*) malloc(sizeof(int) * k);
    int* ugNums  = (int*) malloc(sizeof(int) * k);
    
    uglyNumbers[0] = 1;
    
    for(int i = 1; i < n; i++){
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         */
        int minUgly = INT_MAX;
        
        for(int j = 0; j < k; j++){
            /* Possible weaknesses found:
             *  Cannot determine that 'primes[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'indices[j]' is initialized [premium-bughuntingUninit]
             */
            ugNums[j] = uglyNumbers[indices[j]] * primes[j];
            
            if(ugNums[j] < minUgly){
                minUgly = ugNums[j];
            }
        }
        
        uglyNumbers[i] = minUgly;
        
        for(int j = 0; j < k; j++){
            if(minUgly == ugNums[j]){
                /* Possible weaknesses found:
                 *  Cannot determine that 'indices[j]' is initialized [premium-bughuntingUninit]
                 */
                indices[j]++;
            }
        }
    }
    
    int nthUgly = uglyNumbers[n-1];
    
    /* Possible weaknesses found:
     *  Cannot determine that 'uglyNumbers[0]' is initialized [premium-bughuntingUninit]
     */
    free(uglyNumbers);
    /* Possible weaknesses found:
     *  Cannot determine that 'indices[0]' is initialized [premium-bughuntingUninit]
     */
    free(indices);
    /* Possible weaknesses found:
     *  Cannot determine that 'ugNums[0]' is initialized [premium-bughuntingUninit]
     */
    free(ugNums);
    
    return nthUgly;
}

int main() {
    int n = 6;
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes)/sizeof(primes[0]);
    
    int nthUgly = nthSuperUglyNumber(n, primes, k);
    
    printf("The %dth super ugly number is: %d", n, nthUgly);
    
    return 0;
}