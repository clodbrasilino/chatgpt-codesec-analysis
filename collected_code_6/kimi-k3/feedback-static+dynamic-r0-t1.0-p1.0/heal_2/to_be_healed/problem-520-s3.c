#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1111111117 * 3 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000001,time:10503,execs:468,op:havoc,rep:2)
     * UBSan: signed integer overflow: -7 * -1094795586 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:534,execs:209,op:havoc,rep:2)
     */
    return (a / gcd(a, b)) * b;
}

int findLCM(const int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:16,execs:17,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int result = findLCM(arr, n);
    printf("LCM of the given array elements is: %d\n", result);
    free(arr);
    return 0;
}