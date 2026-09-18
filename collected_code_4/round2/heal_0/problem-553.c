#include <stdio.h>
#include <stdlib.h>

double tupleToFloat(int num1, int num2) {
    char tuple[50];
    sprintf(tuple, "%d.%d", num1, num2);
    return atof(tuple);
}

int main(){
    int num1 = 3, num2 = 14;
    double result = tupleToFloat(num1, num2);

    printf("The floating point number from given tuple is: %f\n", result);

    return 0;
}