#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int kadane(int arr[], int n) {
    int maxSoFar = INT_MIN, maxEndingHere = 0;
    for (int i = 0; i < n; i++) {
        maxEndingHere += arr[i];
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
        if (maxEndingHere < 0)
            maxEndingHere = 0;
    }
    return maxSoFar;
}

int circularKadane(int arr[], int n, int k) {
    int nonCircularMax = kadane(arr, n);
    int arrSum = 0, maxWrap = 0, minKadane = INT_MAX;

    for (int i = 0; i < n; i++) {
        arrSum += arr[i];
        arr[i] = -arr[i];
    }

    minKadane = kadane(arr, n);
    maxWrap = arrSum + minKadane;

    if (k == 1)
        return nonCircularMax;
    else if (nonCircularMax > 0)
        return (nonCircularMax > maxWrap) ? nonCircularMax : maxWrap;
    else
        return maxWrap;
}

int main() {
    int arr[] = {11, -4, 13, -5, 2};
    int n = 5;
    int k = 3;
    int result = circularKadane(arr, n, k);
    printf("The largest sum of contiguous array: %d\n", result);
    return 0;
}