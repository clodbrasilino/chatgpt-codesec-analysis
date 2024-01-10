#include <stdio.h>

int calculateMaxAggregate(int arr[][2], int size) {
    int maxAgg = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[i][1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int sum = arr[i][0] + arr[i][1];
        if (sum > maxAgg) {
            maxAgg = sum;
        }
    }
    return maxAgg;
}

int main() {
    int tuples[][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    
    int maxAggregate = calculateMaxAggregate(tuples, size);
    
    printf("Maximum aggregate: %d\n", maxAggregate);
    
    return 0;
}