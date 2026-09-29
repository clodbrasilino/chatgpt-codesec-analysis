#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int x = nums1Size;
    int y = nums2Size;

    int low = 0;
    int high = x;

    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;

        int maxX = (partitionX == 0) ? -2147483648 : nums1[partitionX - 1];
        int maxY = (partitionY == 0) ? -2147483648 : nums2[partitionY - 1];

        int minX = (partitionX == x) ? 2147483647 : nums1[partitionX];
        int minY = (partitionY == y) ? 2147483647 : nums2[partitionY];

        if (maxX <= minY && maxY <= minX) {
            if ((x + y) % 2 == 0) {
                return ((double)(maxX > maxY ? maxX : maxY) + (double)(minX < minY ? minX : minY)) / 2.0;
            } else {
                return (double)(maxX > maxY ? maxX : maxY);
            }
        } else if (maxX > minY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }

    return 0.0;
}

int main() {
    int nums1[] = {1, 3, 8, 9, 15};
    int nums2[] = {7, 11, 18, 19, 21, 25};

    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);

    double median = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);

    printf("Median is %f\n", median);

    return 0;
}