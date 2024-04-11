#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

float tupleToFloat(char *tuple) {
    float result;
    result = atof(tuple);
    return result;
}

int main() {
    char tuple[] = "(3.14)";
    float floatNum;

    // Removing the parentheses
    for(int i = 0; tuple[i]; i++){
        /* Possible weaknesses found:
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         *  valid subscripts for 'tuple' are '[0]' to '[6]'
         *  read of 1 byte from after the end of 'tuple'
         *  use of uninitialized value 'tuple[<unknown>]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        tuple[i] = tuple[i + 1];
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'strlen'
     */
    tuple[strlen(tuple) - 2] = '\0';

    floatNum = tupleToFloat(tuple);
    printf("The floating point number is: %.2f\n", floatNum);

    return 0;
}