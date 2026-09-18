#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log2'
  */

int getRightmostSetBit(int n) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'log2' [-Wbuiltin-declaration-mismatch]
     *  include '<math.h>' or provide a declaration of 'log2'
     *  implicit declaration of function 'log2' [-Wimplicit-function-declaration]
     */
    return log2(n & -n) + 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    
    int position = getRightmostSetBit(n);
    printf("The position of the rightmost set bit is: %d", position);
    
    return 0;
}