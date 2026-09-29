#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_max_difference(int *arr, size_t n) {
    if (n < 2) {
        return -1;
    }
    
    int min_val = arr[0];
    int max_diff = arr[1] - arr[0];
    
    for (size_t i = 1; i < n; i++) {
        if (arr[i] - min_val > max_diff) {
            max_diff = arr[i] - min_val;
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    
    return max_diff;
}

int main(void) {
    int tuple_list[] = {2, 3, 1, 7, 9, 5, 11, 8, 4};
    size_t n = sizeof(tuple_list) / sizeof(tuple_list[0]);
    
    int result = find_max_difference(tuple_list, n);
    
    printf("%d\n", result);
    
    return 0;
}