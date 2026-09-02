#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 */
int findExtraElementIndex(int *arr1, int *arr2, int n) {
    for (int i = 0; i < n; ++i) {
        if (arr1[i] != arr2[i]) {
            return i;
        }
    }
    return n;
}

int main() {
    int arr1[] = {2, 4, 6, 8, 9, 10, 12};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int n = sizeof(arr2) / sizeof(arr2[0]);

    int index = findExtraElementIndex(arr1, arr2, n);
    printf("Index of the extra element is: %d\n", index);

    return 0;
}