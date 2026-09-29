#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int countEqualPairs(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    int n;
    
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input\n");
            free(arr);
            return 1;
        }
    }
    
    int result = countEqualPairs(arr, n);
    printf("Number of equal element pairs: %d\n", result);
    
    free(arr);
    return 0;
}