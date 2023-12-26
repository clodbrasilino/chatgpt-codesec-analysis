#include <stdio.h>

int findMax(int *tupleRecords, int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleRecords[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int max = tupleRecords[0];
    for (int i = 1; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tupleRecords[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (tupleRecords[i] > max) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tupleRecords[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            max = tupleRecords[i];
        }
    }
    return max;
}

int main() {
    int tupleRecords[] = {10, 15, 8, 20, 12};
    int n = sizeof(tupleRecords) / sizeof(tupleRecords[0]);
    int max = findMax(tupleRecords, n);
    printf("Maximum element: %d\n", max);
    return 0;
}