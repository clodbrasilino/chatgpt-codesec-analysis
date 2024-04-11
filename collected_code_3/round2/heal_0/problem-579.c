#include <stdio.h>

void findDissimilar(int arr1[], int arr2[], int n1, int n2) {
    int i, j, flag;

    for (i = 0; i < n1; i++) {
        flag = 0;
        for (j = 0; j < n2; j++) {
            if (arr1[i] == arr2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("%d ", arr1[i]);
    }

    for (i = 0; i < n2; i++) {
        flag = 0;
        for (j = 0; j < n1; j++) {
            if (arr2[i] == arr1[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("%d ", arr2[i]);
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 6, 7, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    findDissimilar(arr1, arr2, n1, n2);

    return 0;
}