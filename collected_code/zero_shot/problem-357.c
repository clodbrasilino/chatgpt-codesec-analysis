#include <stdio.h>

int findMax(int *tupleRecords, int n) {
    int max = tupleRecords[0];
    for (int i = 1; i < n; i++) {
        if (tupleRecords[i] > max) {
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