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
    size_t pos;
    
    /* Possible weaknesses found:
     *  Value stored to 'pos' is never read [deadcode.DeadStores]
     *  pos is assigned
     */
    pos = left_insertion_point(sorted_array, size, 2);
    /* Possible weaknesses found:
     *  pos is overwritten
     *  Variable 'pos' is reassigned a value before the old one has been used. [redundantAssignment]
     *  Value stored to 'pos' is never read [deadcode.DeadStores]
     *  pos is assigned
     */
    pos = left_insertion_point(sorted_array, size, 4);
    /* Possible weaknesses found:
     *  pos is overwritten
     *  Variable 'pos' is reassigned a value before the old one has been used. [redundantAssignment]
     *  Value stored to 'pos' is never read [deadcode.DeadStores]
     *  pos is assigned
     */
    pos = left_insertion_point(sorted_array, size, 8);
    /* Possible weaknesses found:
     *  pos is overwritten
     *  Variable 'pos' is reassigned a value before the old one has been used. [redundantAssignment]
     */
    pos = left_insertion_point(sorted_array, size, 0);
    
    if (pos == 0) {
        size = 0;
    } else {
        size = pos;
    }
    
    return (int)size;
}