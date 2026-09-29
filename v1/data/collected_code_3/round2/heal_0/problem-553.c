#include <stdio.h>
#include <stdlib.h>

float tupleToFloat(char *tuple) {
    return atof(tuple);
}

int main() {
    char tuple[] = "123.456";
    float result = tupleToFloat(tuple);
    printf("The floating point number is: %.3f\n", result);
    return 0;
}