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
        
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == x) ? INT_MAX : nums1[partitionX];
        
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == y) ? INT_MAX : nums2[partitionY];
        
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((x + y) % 2 == 0) {
                return ((double)(maxLeftX > maxLeftY ? maxLeftX : maxLeftY) + 
                        (double)(minRightX < minRightY ? minRightX : minRightY)) / 2.0;
            } else {
                return (double)(maxLeftX > maxLeftY ? maxLeftX : maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }
    
    return -1.0;
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int size = sizeof(arr1) / sizeof(arr1[0]);
    
    double median = findMedianSortedArrays(arr1, size, arr2, size);
    
    if (median != -1.0) {
        printf("Median: %.2f\n", median);
    } else {
        printf("Error: Invalid input\n");
    }
    
    return 0;
}