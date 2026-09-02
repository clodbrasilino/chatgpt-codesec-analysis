#include <stddef.h>

size_t left_insertion_point(const int *arr, size_t n, int value) {
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
    int sorted_array[] = {1, 2, 2, 2, 3, 5, 7};
    size_t size = sizeof(sorted_array) / sizeof(sorted_array[0]);
    
    size_t pos1 = left_insertion_point(sorted_array, size, 2);
    size_t pos2 = left_insertion_point(sorted_array, size, 4);
    size_t pos3 = left_insertion_point(sorted_array, size, 8);
    size_t pos4 = left_insertion_point(sorted_array, size, 0);
    
    size_t result;
    if (pos4 == 0) {
        result = 0;
    } else {
        result = pos4;
    }
    
    return (int)(pos1 + pos2 + pos3 + result);
}