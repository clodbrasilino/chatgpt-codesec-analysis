#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertTupleStringToIntTuple(char* tupleString, int* intTuple) {
    // Initialize variables
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'tupleString[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int tupleSize = strlen(tupleString) / 2;
    char* token;
  
    // Split the tuple string into individual values
    token = strtok(tupleString, ",");
    int i = 0;
  
    while (token != NULL && i < tupleSize) {
        /* Possible weaknesses found:
         *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
         */
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
        /* Possible weaknesses found:
         *  Cannot determine that 'intTuple[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", intTuple[i]);
    }
  
    return 0;
}