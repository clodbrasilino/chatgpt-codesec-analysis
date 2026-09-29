#include <stdio.h>
#include <stdlib.h>

float tupleToFloat(char *tuple) {
    return atof(tuple);
}

int main() {
    char tuple[] = "3.14";
    float result = tupleToFloat(tuple);
    printf("The floating point number is: %.2f\n", result);
    return 0;
}