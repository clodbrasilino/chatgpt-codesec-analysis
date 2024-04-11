#include <stdio.h>

int findSingle(int arr[], int arr_size)
{
    int low = 0, high = arr_size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (mid % 2 == 0) {
            if (arr[mid] == arr[mid + 1])
                low = mid + 2;
            else
                high = mid;
        }
        else {
            if (arr[mid] == arr[mid - 1])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return arr[low];
}

int main()
{
    int arr[] = {1, 1, 2, 4, 4, 5, 5, 6, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", findSingle(arr, n));
    return 0;
}