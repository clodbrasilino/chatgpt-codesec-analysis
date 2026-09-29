#include <stdio.h>
#include <stdlib.h>

float tupleToFloat(char *tuple) {
    float num;
    num = atof(tuple);
    return num;
}

int main() {
    char tuple[] = "(123.456)";
    char *tupleNum = tuple + 1;
    tupleNum[strlen(tupleNum) - 1] = '\0';

    float num = tupleToFloat(tupleNum);
    printf("The floating point number is: %.3f\n", num);

    return 0;
}