#include <stddef.h>
#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_last(int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    long low = 0;
    long high = (long)size - 1;
    int result = -1;

    while (low <= high) {
        long mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = (int)mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    int target = 2;
    int pos = find_last(arr, size, target);
    printf("%d\n", pos);

    target = 6;
    pos = find_last(arr, size, target);
    printf("%d\n", pos);

    pos = find_last(NULL, size, target);
    printf("%d\n", pos);

    pos = find_last(arr, 0, target);
    printf("%d\n", pos);

    return 0;
}