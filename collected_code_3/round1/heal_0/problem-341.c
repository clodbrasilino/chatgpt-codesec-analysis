#include <stdio.h>

#define MAX 100

void convertToOrderedTuples(int arr[], int n) {
    int i, j;
    for(i = 0; i < n; i+=2) {
        printf("(%d, %d)\n", arr[i], arr[i+1]);
    }
}

int main() {
    int arr[MAX], n, i;
    printf("Enter the number of elements in the set: ");
    scanf("%d", &n);
    printf("Enter the elements of the set: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    convertToOrderedTuples(arr, n);
    return 0;
}