#include<stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int operationsRequired(int arr[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    if (sum % n != 0)
        return -1;
    int x = sum / n, res = 0;
    for (int i = 0; i < n; i++)
        /* Possible weaknesses found:
         *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
         */
        res += abs(x - arr[i]);
    return res / 2;
}

int main() {
    int arr[] = {1, 1, 2, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int res = operationsRequired(arr, n);
    if (res != -1)
        printf("%d\n", res);
    else
        printf("No solution\n");
    return 0;
}