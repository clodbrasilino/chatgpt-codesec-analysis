#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int minNumberToMakeSumEven(int arr[], int n) {
    int sum = 0;
    int i;
    
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    if (sum % 2 == 0) {
        return 0;
    }
    
    return 1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("%d\n", minNumberToMakeSumEven(arr, n));
    
    return 0;
}