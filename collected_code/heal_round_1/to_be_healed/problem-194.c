#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

int convertOctalToDecimal(int octalNumber) {
    int decimalNumber = 0, i = 0;
    
    while (octalNumber != 0) {
        /* Possible weaknesses found:
         *  include '<math.h>' or provide a declaration of 'pow'
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'pow' [-Wbuiltin-declaration-mismatch]
         */
        decimalNumber += (octalNumber % 10) * pow(8, i);
        ++i;
        octalNumber /= 10;
    }
    
    return decimalNumber;
}

int main() {
    int octalNumber;
    
    printf("Enter an octal number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'octalNumber' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &octalNumber);
    
    printf("Decimal number: %d", convertOctalToDecimal(octalNumber));
    
    return 0;
}