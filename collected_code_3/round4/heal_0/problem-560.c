#include <stdio.h>

#define MAX 100

void findUnion(int arr1[], int arr2[], int m, int n) {
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (arr1[i] < arr2[j])
            printf(" %d ", arr1[i++]);
        else if (arr2[j] < arr1[i])
            printf(" %d ", arr2[j++]);
        else {
            printf(" %d ", arr2[j++]);
            i++;
        }
    }
    while(i < m)
        printf(" %d ", arr1[i++]);
    while(j < n)
        printf(" %d ", arr2[j++]);
}

int main() {
    int arr1[MAX], arr2[MAX], m, n, i;
    printf("Enter number of elements in first array: ");
    scanf("%d", &m);
    printf("Enter elements of first array: ");
    for(i = 0; i < m; i++)
        scanf("%d", &arr1[i]);
    printf("Enter number of elements in second array: ");
    scanf("%d", &n);
    printf("Enter elements of second array: ");
    for(i = 0; i < n; i++)
        scanf("%d", &arr2[i]);
    printf("Union of two arrays is: ");
    findUnion(arr1, arr2, m, n);
    return 0;
}