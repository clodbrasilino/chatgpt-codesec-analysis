#include <stdio.h>

int countElementsInRange(int list[], int size, int lower, int upper) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
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