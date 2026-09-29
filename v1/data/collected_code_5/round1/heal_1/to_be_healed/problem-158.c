#include <stdio.h>

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
         *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
         *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
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