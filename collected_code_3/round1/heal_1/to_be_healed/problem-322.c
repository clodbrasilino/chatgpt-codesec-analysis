#include <stdio.h>
#include <stdlib.h>

void find_min_positions(int *arr, int n) {
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     *  use of uninitialized value '*arr' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    int min = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    printf("Minimum value is at positions: ");
    for(int i = 0; i < n; i++) {
        if(arr[i] == min) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    find_min_positions(arr, n);
    free(arr);
    return 0;
}