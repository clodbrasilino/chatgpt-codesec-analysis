#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log2'
  */

// Function to get the rightmost set bit
int rightmostSetBit(int n){
    if (n == 0) {
        return -1;
    }
    /* Possible weaknesses found:
     *  include '<math.h>' or provide a declaration of 'log2'
     *  implicit declaration of function 'log2' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'log2' [-Wbuiltin-declaration-mismatch]
     */
    return log2(n & -n) + 1;
}

// Main function
int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int position = rightmostSetBit(n);
    if (position == -1) {
        printf("There are no set bits in the number.\n");
    } else {  
        printf("The position of the rightmost set bit in the number is %d.\n", position);
    }

    return 0;
}