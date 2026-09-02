#include <stdio.h>

void rearrange(int arr[], int n) {
    int pos = 0, neg = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;
    
    while (1) {
        while (pos < n && arr[pos] >= 0) pos += 2;
        while (neg < n && arr[neg] < 0) neg += 2;
        
        if (pos >= n || neg >= n) break;
        
        temp = arr[pos];
        arr[pos] = arr[neg];
        arr[neg] = temp;
    }
}

int main(void) {
    int arr[] = {1, 2, 3, -4, -1, 4, -3, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;
    
    rearrange(arr, n);
    
    for (i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
    
    return 0;
}