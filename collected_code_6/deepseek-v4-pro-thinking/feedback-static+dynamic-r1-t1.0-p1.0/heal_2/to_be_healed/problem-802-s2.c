#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

int countRotations(const int arr[], int n) {
    int low;
    int high;

    if (arr == NULL || n <= 0) {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low < high) {
        /* Possible weaknesses found:
         *  mid is assigned 'low+(high-low)/2' here.
         */
        int mid = low + (high - low) / 2;

        /* Possible weaknesses found:
         *  Negative array index
         *  Either the condition 'high>0' is redundant or the array 'arr[0]' is accessed at index -2, which is out of bounds. [negativeIndex]
         *  Either the condition 'high>0' is redundant or the array 'arr[0]' is accessed at index -1, which is out of bounds. [negativeIndex]
         */
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            /* Possible weaknesses found:
             *  Assuming that condition 'high>0' is not redundant
             */
            if (high > 0 && arr[high] < arr[high - 1]) {
                return high;
            }
            /* Possible weaknesses found:
             *  high is decremented', new value is -1
             */
            high--;
        }
    }

    return low;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int rotations = countRotations(arr, n);

    if (rotations >= 0) {
        printf("%d\n", rotations);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}