#include <stdio.h>
#include <limits.h>

int minJumps(const int arr[], int n) {
    if (n <= 1) return 0;
    if (arr[0] == 0) return -1;

    int maxReach = arr[0];
    int step = arr[0];
    int jump = 1;

    for (int i = 1; i < n; i++) {
        if (i == n - 1) return jump;
        maxReach = (maxReach > i + arr[i]) ? maxReach : i + arr[i];
        step--;
        if (step == 0) {
            jump++;
            if (i >= maxReach) return -1;
            step = maxReach - i;
        }
    }
    return -1;
}

int main() {
    const int test_cases[][5] = {
        {2, 3, 1, 1, 4},
        {1, 1, 1, 1, 1},
        {1, 2, 3, 0, 0, 3, 2, 1, 0, 1, 0, 0, 0, 1}
    };
    int expected[] = {3, 4, 7};

    for (int i = 0; i < 3; i++) {
        int n = sizeof(test_cases[i]) / sizeof(test_cases[i][0]);
        int result = minJumps(test_cases[i], n);
        printf("Test case %d: Expected %d, got %d\n", i + 1, expected[i], result);
    }

    return 0;
}