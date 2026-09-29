#include<stdio.h>
#include<limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int minDiff(int arr[], int n)
{
   int i, j, diff, min_diff = INT_MAX;
   for(i = 0; i < n-1; i++)
   {
      for(j = i+1; j < n; j++)
      {
         /* Possible weaknesses found:
          *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
          */
         if(abs(arr[i] - arr[j]) < min_diff)
         {
            min_diff = abs(arr[i] - arr[j]);
         }
      }
   }
   return min_diff == INT_MAX ? -1 : min_diff;
}

int main()
{
   int arr[] = {5, 30, 15, 10, 3};
   int size = sizeof(arr) / sizeof(arr[0]);
   
   int result = minDiff(arr, size);
   if (result == -1)
       printf("Array does not have enough elements\n");
   else 
       printf("Minimum difference is %d\n", result );
   return 0;
}