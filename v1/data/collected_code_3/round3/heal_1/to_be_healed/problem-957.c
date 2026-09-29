#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log2'
  */

int getRightmostSetBit(int n) {
    /* Possible weaknesses found:
     *  include '<math.h>' or provide a declaration of 'log2'
     *  incompatible implicit declaration of built-in function 'log2' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'log2' [-Wimplicit-function-declaration]
     */
    return log2(n & -n) + 1;
}

int main() {
    int n = 18;
    printf("%d", getRightmostSetBit(n));
    return 0;
}