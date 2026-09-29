#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

void maxProductPair(int arr[], int n)
{
    if (n < 2)
    {
        printf("No pairs exists\n");
        return;
    }

    if (n == 2)
    {
        printf("%d %d", arr[0], arr[1]);
        return;
    }

    int posa = INT_MIN, posb = INT_MIN;
    int nega = INT_MIN, negb = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > posa)
        {
            posb = posa;
            posa = arr[i];
        }
        else if (arr[i] > posb)
            posb = arr[i];

        /* Possible weaknesses found:
         *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
         */
        if (arr[i] < 0 && abs(arr[i]) > abs(nega))
        {
            negb = nega;
            nega = arr[i];
        }
        else if(arr[i] < 0 && abs(arr[i]) > abs(negb))
            negb = arr[i];
    }

    if (nega*negb > posa*posb)
        printf("%d %d", nega, negb);
    else
        printf("%d %d", posa, posb);
}

int main()
{
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    maxProductPair(arr, n);
    return 0;
}