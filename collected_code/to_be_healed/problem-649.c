#include <stdio.h>

int calculateSum(int list[], int size, int start, int end) {
    if (start < 0 || start >= size || end < 0 || end >= size) {
        printf("Invalid range\n");
        return 0;
    }
    int sum = 0;
    for (int i = start; i <= end; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += list[i];
    }
    return sum;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);
    int start = 2;
    int end = 6;
    int sum = calculateSum(list, size, start, end);
    printf("Sum of the numbers between indices %d and %d: %d\n", start, end, sum);
    return 0;
}