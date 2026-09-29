#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

void findPerfectSquares(int start, int end) {
    int i;
    
    for(i = start; i <= end; i++) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
         *  include '<math.h>' or provide a declaration of 'sqrt'
         */
        int squareRoot = sqrt(i);
        
        if (squareRoot * squareRoot == i) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int start, end;
    
    printf("Enter the start number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'start' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &start);
    printf("Enter the end number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'end' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &end);
    
    printf("Perfect squares between %d and %d are:\n", start, end);
    findPerfectSquares(start, end);
    
    return 0;
}