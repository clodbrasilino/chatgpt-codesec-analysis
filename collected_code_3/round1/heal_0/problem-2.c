#include <stdio.h>

#define MAX 100

void findSimilar(int arr1[], int arr2[], int n1, int n2) {
    int i, j;
    for (i = 0; i < n1; i++) {
        for (j = 0; j < n2; j++) {
            if (arr1[i] == arr2[j]) {
                printf("%d ", arr1[i]);
                break;
            }
        }
    }
}

int main() {
    int arr1[MAX], arr2[MAX], n1, n2, i;

    printf("Enter the number of elements in first array: ");
    scanf("%d", &n1);
    printf("Enter elements of first array: ");
    for (i = 0; i < n1; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the number of elements in second array: ");
    scanf("%d", &n2);
    printf("Enter elements of second array: ");
    for (i = 0; i < n2; i++) {
        scanf("%d", &arr2[i]);
    }

    printf("Similar elements are: ");
    findSimilar(arr1, arr2, n1, n2);

    return 0;
}