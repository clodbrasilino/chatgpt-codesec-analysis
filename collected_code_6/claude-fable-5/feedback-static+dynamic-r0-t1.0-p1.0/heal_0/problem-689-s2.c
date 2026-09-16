#include <stdio.h>
#include <limits.h>

int minJumps(const int *arr, int n);

int minJumps(const int *arr, int n)
{
    int jumps;
    int currentEnd;
    int farthest;
    int i;

    if (arr == NULL || n <= 0) {
        return -1;
    }

    if (n == 1) {
        return 0;
    }

    if (arr[0] <= 0) {
        return -1;
    }

    jumps = 0;
    currentEnd = 0;
    farthest = 0;

    for (i = 0; i < n - 1; i++) {
        if (arr[i] > 0 && i + arr[i] > farthest) {
            if (arr[i] > INT_MAX - i) {
                farthest = INT_MAX;
            } else {
                farthest = i + arr[i];
            }
        }

        if (i == currentEnd) {
            if (farthest <= currentEnd) {
                return -1;
            }
            jumps++;
            currentEnd = farthest;
            if (currentEnd >= n - 1) {
                return jumps;
            }
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {2, 3, 1, 1, 4};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result;

    result = minJumps(arr, n);

    if (result < 0) {
        if (printf("End of array is not reachable\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Minimum number of jumps: %d\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}