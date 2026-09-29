#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertTupleStringToIntTuple(char* tupleString, int* intTuple) {
    // Initialize variables
    int tupleSize = strlen(tupleString) / 2;
    char* token;
  
    // Split the tuple string into individual values
    token = strtok(tupleString, ",");
    int i = 0;
  
    while (token != NULL && i < tupleSize) {
        intTuple[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
}

int main() {
    // Example usage
    char tupleString[] = "1,2,3,4,5";
    int intTuple[5];
  
    convertTupleStringToIntTuple(tupleString, intTuple);
  
    for (int i = 0; i < sizeof(intTuple) / sizeof(int); i++) {
        printf("%d ", intTuple[i]);
    }
  
    return 0;
}