#include<stdio.h>

void extractTuples(int tuple1[], int tuple2[], int result[], int size) {
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple2[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        result[i] = tuple1[i] & tuple2[i];
    }
}

int main() {
    // Example usage
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {2, 3, 4};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    int result[size];

    extractTuples(tuple1, tuple2, result, size);

    // Print the resulting tuple
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'result[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", result[i]);
    }
    
    return 0;
}