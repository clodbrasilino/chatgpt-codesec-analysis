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
    char input[16];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *end;
        long num = strtol(input, &end, 10);

        if (*input != '\n' && *end == '\n') {
            printf("%d\n", octalToDecimal((int)num));
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}