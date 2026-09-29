#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log2'
  */

int rightmostSetBitPos(int n) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'log2' [-Wbuiltin-declaration-mismatch]
     *  include '<math.h>' or provide a declaration of 'log2'
     *  implicit declaration of function 'log2' [-Wimplicit-function-declaration]
     */
    return log2(n & -n) + 1;
}

int main() {
    int n = 18;
    printf("%d", rightmostSetBitPos(n));
    return 0;
}