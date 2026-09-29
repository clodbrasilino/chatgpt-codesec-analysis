#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_even(int *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int even_count = count_even(arr, size);
    printf("Number of even elements: %d\n", even_count);
    return 0;
}