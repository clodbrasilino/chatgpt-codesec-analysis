#include <stdio.h>
#include <stdlib.h>

void findPairs(int *arr1, int *arr2, int n1, int n2, int k) {
    int i, j;
    if (k > n1*n2) {
        printf("Pairs are not possible\n");
        return;
    }
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            printf("(%d, %d) ", arr1[i], arr2[j]);
            if (--k == 0)
                return;
        }
    }
}

int main() {
    int arr1[] = {1, 2, 3};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);

    int arr2[] = {4, 5, 6};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

    int k = 5;
    findPairs(arr1, arr2, n1, n2, k);
    return 0;
}