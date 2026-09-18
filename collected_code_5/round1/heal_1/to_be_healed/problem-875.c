#include<stdio.h>
#include<limits.h>

int minDiff(int arr[], int n)
{
   int i, j, diff, min_diff = INT_MAX;
   for(i = 0; i < n-1; i++)
   {
      for(j = i+1; j < n; j++)
      {
         /* Possible weaknesses found:
          *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
          *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
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