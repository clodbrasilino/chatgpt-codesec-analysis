#include <stdio.h>

int binary_search(int arr[], int len, int value) {
    int low = 0;
    int high = len;

    while (low < high) {
        int mid = (low + high) / 2;
        if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

int main() {
    int array[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int len = sizeof(array) / sizeof(array[0]);

    int value = 10;
    int index = binary_search(array, len, value);

    printf("The right place to insert %d in sorted order is at index %d\n", value, index);

    return 0;
}