#include <stdio.h>

int findMinimum(const int *periodicFunction, int size) {
    int minValue = *periodicFunction;
    for (int i = 1; i < size; i++) {
        if (*(periodicFunction + i) < minValue) {
            minValue = *(periodicFunction + i);
        }
    }
    return minValue;
}

int main() {
    int periodicFunction[] = {5, 2, 9, 3, 7, 1, 6};
    int size = sizeof(periodicFunction) / sizeof(periodicFunction[0]);
    int minimumValue = findMinimum(periodicFunction, size);
    printf("Minimum value: %d\n", minimumValue);
    return 0;
}