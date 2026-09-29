#include <stddef.h>

size_t find_insertion_point(const int *arr, size_t n, int value) {
    size_t low = 0;
    size_t high = n;
    
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    
    return low;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int value = 6;
    
    /* Possible weaknesses found:
     *  Variable 'pos' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'pos' during its initialization is never read [deadcode.DeadStores]
     */
    size_t pos = find_insertion_point(arr, n, value);
    
    return 0;
}