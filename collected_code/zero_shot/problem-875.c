#include <stdio.h>
#include <stdlib.h>

int minDifference(int tuple1[], int tuple2[], int size) {
    int minDiff = abs(tuple1[0] - tuple2[0]);
    for (int i = 0; i < size; i++) {
        int diff = abs(tuple1[i] - tuple2[i]);
        if (diff < minDiff) {
            minDiff = diff;
        }
    }
    return minDiff;
}

int main() {
    int tuple1[] = {1, 8, 3};
    int tuple2[] = {5, 2, 7};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);
    int minDiff = minDifference(tuple1, tuple2, size);
    printf("Minimum difference: %d\n", minDiff);
    return 0;
}