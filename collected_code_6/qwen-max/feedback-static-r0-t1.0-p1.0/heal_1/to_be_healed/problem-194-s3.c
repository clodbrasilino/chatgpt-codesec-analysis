#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

int octalToDecimal(int octal) {
    int decimal = 0, i = 0;
    while (octal != 0) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         */
        decimal += (octal % 10) * pow(8, i);
        ++i;
        octal /= 10;
    }
    return decimal;
}

int main() {
    int octal;
    printf("Enter an octal number: ");
    if (scanf("%d", &octal) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    for ( ; octal > 0; octal /= 10) {
        if (octal % 10 >= 8) {
            fprintf(stderr, "Invalid octal number.\n");
            return EXIT_FAILURE;
        }
    }

    int decimal = octalToDecimal(octal);
    printf("Decimal equivalent: %d\n", decimal);

    return EXIT_SUCCESS;
}