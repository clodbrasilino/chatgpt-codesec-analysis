#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

float tupleToFloat(char *tuple) {
    float num;
    num = atof(tuple);
    return num;
}

int main() {
    char tuple[] = "(123.456)";
    char *tupleNum = tuple + 1;
    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    tupleNum[strlen(tupleNum) - 1] = '\0';

    float num = tupleToFloat(tupleNum);
    printf("The floating point number is: %.3f\n", num);

    return 0;
}