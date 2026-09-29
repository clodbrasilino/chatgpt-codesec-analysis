#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float tupleToFloat(char *tuple) {
    float result;
    result = atof(tuple);
    return result;
}

int main() {
    char tuple[] = "(3.14)";
    int length = strlen(tuple);
    float floatNum;
    char newTuple[length - 2];

    memcpy(newTuple, &tuple[1], length - 2);
    newTuple[length - 2] = '\0';

    floatNum = tupleToFloat(newTuple);
    printf("The floating point number is: %.2f\n", floatNum);

    return 0;
}