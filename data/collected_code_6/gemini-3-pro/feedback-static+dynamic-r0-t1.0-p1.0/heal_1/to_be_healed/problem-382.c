#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findRotationCount(int arr[], int n) {
    if (n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    if (arr[low] <= arr[high]) {
        return 0;
    }

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else if (arr[mid] >= arr[low]) {
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int count1 = findRotationCount(arr1, n1);
    if (count1 != -1) {
        printf("%d\n", count1);
    } else {
        printf("-1\n");
    }

    int arr2[] = {7, 9, 11, 12, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int count2 = findRotationCount(arr2, n2);
    if (count2 != -1) {
        printf("%d\n", count2);
    } else {
        printf("-1\n");
    }

    int arr3[] = {7, 9, 11, 12, 15};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int count3 = findRotationCount(arr3, n3);
    if (count3 != -1) {
        printf("%d\n", count3);
    } else {
        printf("-1\n");
    }

    return 0;
}