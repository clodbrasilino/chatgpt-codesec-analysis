#include <stdio.h>
#include <stdbool.h>

bool isDecreasingTrend(const int *numbers, int length) {
    if (length <= 1) {
        return false;
    }
    for (int i = 1; i < length; ++i) {
        if (numbers[i] >= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int test1[] = {5, 4, 3, 2, 1};
    int test2[] = {1, 2, 3, 4, 5};
    int test3[] = {5, 3, 6, 2, 1};

    int len1 = sizeof(test1) / sizeof(test1[0]);
    int len2 = sizeof(test2) / sizeof(test2[0]);
    int len3 = sizeof(test3) / sizeof(test3[0]);

    printf("Test 1: %s\n", isDecreasingTrend(test1, len1) ? "Decreasing" : "Not Decreasing");
    printf("Test 2: %s\n", isDecreasingTrend(test2, len2) ? "Decreasing" : "Not Decreasing");
    printf("Test 3: %s\n", isDecreasingTrend(test3, len3) ? "Decreasing" : "Not Decreasing");

    return 0;
}