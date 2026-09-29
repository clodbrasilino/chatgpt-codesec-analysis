#include <stdio.h>

int countElementsInRange(const int list[], int size, int lower, int upper) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }
    return count;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);
    int lower = 3;
    int upper = 7;
    int result = countElementsInRange(list, size, lower, upper);
    printf("Number of elements in range: %d\n", result);
    return 0;
}