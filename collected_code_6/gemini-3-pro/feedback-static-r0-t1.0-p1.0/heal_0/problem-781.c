#include <stdio.h>
#include <math.h>

int hasEvenDivisorCount(int n) {
    if (n <= 0) {
        return 0;
    }
    int root = (int)sqrt((double)n);
    if (root * root == n) {
        return 0;
    }
    return 1;
}

int main(void) {
    int testCases[] = {1, 2, 3, 4, 10, 16, 25, 36, -5, 0};
    size_t numCases = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numCases; i++) {
        int result = hasEvenDivisorCount(testCases[i]);
        if (testCases[i] > 0) {
            printf("%d: %s\n", testCases[i], result ? "Even" : "Odd");
        } else {
            printf("%d: Invalid input\n", testCases[i]);
        }
    }

    return 0;
}