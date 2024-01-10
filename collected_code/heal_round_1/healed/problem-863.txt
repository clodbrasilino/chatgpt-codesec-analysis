#include <stdio.h>

int findLongestSubsequence(const int arr[], int n)
{
    int maxCount = 1, currentCount = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] - arr[i - 1] == 1) {
            currentCount++;
        } 
        else if (arr[i] != arr[i - 1]) {
            if (currentCount > maxCount) {
                maxCount = currentCount;
            }
            currentCount = 1;
        }
    }

    if (currentCount > maxCount) {
        maxCount = currentCount;
    }

    return maxCount;
}

int main()
{
    int arr[] = {1, 2, 3, 5, 6, 7, 15, 16, 17, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    int length = findLongestSubsequence(arr, n);

    printf("Length of longest subsequence: %d", length);

    return 0;
}