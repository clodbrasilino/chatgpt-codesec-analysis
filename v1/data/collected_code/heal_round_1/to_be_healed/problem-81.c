#include <stdio.h>

// Function to zip two given tuples
void zipTuples(int tuple1[], int tuple2[], int size) {
    // Initialize a new array with double the size
    int zipTuple[size * 2];
    
    // Zip the tuples by merging them
    for (int i = 0; i < size * 2; i += 2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple1[i/2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        zipTuple[i] = tuple1[i / 2];
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i/2]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        zipTuple[i + 1] = tuple2[i / 2];
    }
    
    // Print the zip tuple
    printf("Zip Tuple: ");
    for (int i = 0; i < size * 2; i++) {
        printf("%d ", zipTuple[i]);
    }
}

int main() {
    // Example tuples
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    
    // Calculate the size of the tuples
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    // Zip the tuples
    zipTuples(tuple1, tuple2, size);
    
    return 0;
}