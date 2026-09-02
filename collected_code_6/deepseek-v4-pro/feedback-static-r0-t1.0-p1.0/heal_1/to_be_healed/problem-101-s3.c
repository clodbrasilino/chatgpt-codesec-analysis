#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_kth_element(int *arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size) {
        return -1;
    }
    
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    int result = temp[k];
    free(temp);
    return result;
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    int result = find_kth_element(arr, size, k);
    if (result != -1) {
        printf("The %dth element is: %d\n", k, result);
    } else {
        printf("Invalid input parameters\n");
    }
    
    return 0;
}