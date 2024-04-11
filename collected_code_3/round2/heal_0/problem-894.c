#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float first;
    float second;
} Tuple;

Tuple stringToTuple(char* str) {
    Tuple result;
    char* token = strtok(str, ",");
    result.first = atof(token);
    token = strtok(NULL, ",");
    result.second = atof(token);
    return result;
}

int main() {
    char str[] = "3.14,2.71";
    Tuple result = stringToTuple(str);
    printf("First: %.2f, Second: %.2f\n", result.first, result.second);
    return 0;
}