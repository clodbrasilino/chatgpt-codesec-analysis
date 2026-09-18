#include <stdio.h>

int sumElementsInRange(int *list, int start, int end) {
    int sum = 0;

    if (start < 0 || end < start) {
        printf("Improper range indices\n");
        return -1;
    }

    for (int i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 2;
    int end = 6;
    int sumInRange;

    sumInRange = sumElementsInRange(list, start, end);

    if (sumInRange != -1) {
        printf("Sum of numbers in range %d to %d is %d\n", start, end, sumInRange);
    }
    return 0;
}