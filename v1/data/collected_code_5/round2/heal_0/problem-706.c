#include <stdio.h>
#include <stdbool.h>

#define MAX 100

bool isArraySubset(int arr1[], int arr2[], int m, int n) {
    int i = 0;
    int j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (arr2[i] == arr1[j])
                break;
        }
        if (j == m)
            return false;
    }
    return true;
}

int main() {
    int arr1[MAX], arr2[MAX];
    int m, n, i;
    
    printf("Enter size of first array: ");
    scanf("%d", &m);
    printf("Enter elements in first array: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &arr1[i]);
    }
    
    printf("Enter size of second array: ");
    scanf("%d", &n);
    printf("Enter elements in second array: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }

    if (isArraySubset(arr1, arr2, m, n))
        printf("Array2 is a subset of Array1\n");
    else
        printf("Array2 is not a subset of Array1\n");
  
    return 0;
}