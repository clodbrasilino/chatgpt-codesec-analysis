#include <stdio.h>

int kthElement(int arr1[], int arr2[], int n1, int n2, int k) {
    int i = 0, j = 0, x = 0;
    while(i < n1 && j < n2) {
        if(arr1[i] < arr2[j]) {
            x++;
            if(x == k)
                return arr1[i];
            i++;
        } else {
            x++;
            if(x == k)
                return arr2[j];
            j++;
        }
    }
    while(i < n1) {
        x++;
        if(x == k)
            return arr1[i];
        i++;
    }
    while(j < n2) {
        x++;
        if(x == k)
            return arr2[j];
        j++;
    }
    return -1;
}

int main() {
    int arr1[] = {2, 3, 6, 7, 9};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {1, 4, 8, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k = 5;
    printf("K-th element is %d", kthElement(arr1, arr2, n1, n2, k));
    return 0;
}