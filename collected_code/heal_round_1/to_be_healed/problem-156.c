#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a tuple of string values to a tuple of integer values
void convertTupleOfStringToInt(char *input[], int size, int output[]) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
         *  Cannot determine that 'input[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        output[i] = atoi(input[i]);
    }
}

// Example usage
int main() {
    // Sample input and output arrays
    char *input[] = {"1", "2", "3"};
    int size = sizeof(input) / sizeof(input[0]);
    int output[size];

    // Call the function
    convertTupleOfStringToInt(input, size, output);

    // Print the converted tuple
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'output[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", output[i]);
    }

    return 0;
}