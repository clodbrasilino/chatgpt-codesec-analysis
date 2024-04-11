#include <stdio.h>

#define SIZE 5

void findCommon(int arr1[], int arr2[], int arr3[], int n1, int n2, int n3) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2 && k < n3) {
        if (arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
            printf("%d ", arr1[i]);
            i++;
            j++;
            k++;
        } else if (arr1[i] < arr2[j]) {
            i++;
        } else if (arr2[j] < arr3[k]) {
            j++;
        } else {
            k++;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *  excess elements in array initializer
     *  (near initialization for 'arr1')
     */
    int arr1[SIZE] = {1, 5, 10, 20, 40, 80};
    int arr2[SIZE] = {6, 7, 20, 80, 100};
    /* Possible weaknesses found:
     *  excess elements in array initializer
     *  (near initialization for 'arr3')
     */
    int arr3[SIZE] = {3, 4, 15, 20, 30, 70, 80, 120};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Common elements are ");
    findCommon(arr1, arr2, arr3, n1, n2, n3);
    return 0;
}