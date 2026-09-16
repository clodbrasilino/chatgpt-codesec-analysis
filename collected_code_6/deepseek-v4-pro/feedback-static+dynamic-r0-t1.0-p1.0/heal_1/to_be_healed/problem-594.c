#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_difference(int *arr, int size) {
    int first_even = -1;
    int first_odd = -1;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0 && first_even == -1) {
            first_even = arr[i];
        }
        if (arr[i] % 2 != 0 && first_odd == -1) {
            first_odd = arr[i];
        }
        if (first_even != -1 && first_odd != -1) {
            break;
        }
    }
    
    if (first_even == -1 || first_odd == -1) {
        return 0;
    }
    
    return first_even - first_odd;
}

int main(void) {
    int arr[] = {3, 5, 2, 8, 1, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = find_difference(arr, size);
    printf("%d\n", result);
    
    return 0;
}