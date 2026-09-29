#include <stdio.h>

// Function to get the rightmost set bit
int rightmostSetBit(int n){
    if (n == 0) {
        return -1;
    }
    /* Possible weaknesses found:
     *  call to undeclared library function 'log2' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'log2'
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