#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findIndex(int *arr, int size, int num) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int num = 3;
    int index = findIndex(arr, size, num);
    if (index != -1) {
        printf("Index: %d\n", index);
    } else {
        printf("Number not found\n");
    }
    return 0;
}