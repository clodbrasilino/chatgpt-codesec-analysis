#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_smallest(int arr[], int size) {
    int smallest = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }
    }
    return smallest;
}

int main() {
    int arr[] = {12, 5, 8, 3, 17};
    int size = sizeof(arr) / sizeof(arr[0]);
    int smallest = find_smallest(arr, size);
    printf("Smallest number: %d\n", smallest);
    return 0;
}