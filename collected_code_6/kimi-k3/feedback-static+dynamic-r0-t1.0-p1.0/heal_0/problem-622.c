#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double findMedianSortedArrays(const int *nums1, const int *nums2, int n)
{
    if (n <= 0)
    {
        return 0.0;
    }

    int low = 0;
    int high = n;

    while (low <= high)
    {
        int partitionX = (low + high) / 2;
        int partitionY = n - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == n) ? INT_MAX : nums1[partitionX];

        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX)
        {
            int leftMax = (maxLeftX > maxLeftY) ? maxLeftX : maxLeftY;
            int rightMin = (minRightX < minRightY) ? minRightX : minRightY;
            return ((double)leftMax + (double)rightMin) / 2.0;
        }
        else if (maxLeftX > minRightY)
        {
            high = partitionX - 1;
        }
        else
        {
            low = partitionX + 1;
        }
    }

    return 0.0;
}

int main(void)
{
    int nums1[] = {1, 3, 8, 9, 15};
    int nums2[] = {7, 11, 18, 19, 21};
    int n = (int)(sizeof(nums1) / sizeof(nums1[0]));

    double median = findMedianSortedArrays(nums1, nums2, n);
    printf("Median: %.2f\n", median);

    return 0;
}