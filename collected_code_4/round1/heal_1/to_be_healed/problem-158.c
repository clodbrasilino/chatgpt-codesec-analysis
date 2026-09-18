#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int minOper(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    if (sum % n != 0)
        return -1;

    int x = sum / n;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
         */
        ans += abs(x - arr[i]);
    }

    return ans / 2;
}

int main()
{
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = minOper(arr, n);
    
    if (result == -1)
        printf("Not possible\n");
    else
        printf("%d\n", result);
    
    return 0;
}