#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_element_after_rotations(int *arr, int n, int rotations, int index) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    if (index < 0 || index >= n) {
        return -1;
    }
    rotations = rotations % n;
    if (rotations < 0) {
        rotations += n;
    }
    int original_index = (index - rotations + n) % n;
    return arr[original_index];
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = 2;
    int index = 3;
    int result = find_element_after_rotations(arr, n, rotations, index);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}