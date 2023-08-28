#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a tuple of string values to a tuple of integer values
void convertTupleOfStringToInt(char *input[], int size, int output[]) {
    for (int i = 0; i < size; i++) {
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
        printf("%d ", output[i]);
    }

    return 0;
}