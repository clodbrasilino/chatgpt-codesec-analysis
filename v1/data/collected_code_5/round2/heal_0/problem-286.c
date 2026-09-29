#include<stdio.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

int maxSubArraySum(int a[], int size)
{
   int maxSoFar = a[0];
   int currMax = a[0];
 
   for (int i = 1; i < size; i++)
   {
        currMax = max(a[i], currMax+a[i]);
        maxSoFar = max(maxSoFar, currMax);
   }
   return maxSoFar;
}

int maxSubArraySumKRepetition(int a[], int n, int k)
{
    int arraySum = 0;
    for(int i = 0; i < n; i++){
        arraySum += a[i];
    }
    if(k == 1){
        return maxSubArraySum(a,n);
    }
    else{
        int extendedArray[n * 2];
        for(int i = 0; i < n; i++)
        {
            extendedArray[i] = a[i];
            extendedArray[i + n] = a[i];
        }
        int maxSubArraySumDouble = maxSubArraySum(extendedArray, 2*n);
        return max(maxSubArraySumDouble, arraySum * k);
    }
}

int main()
{
   int a[] =  {-2, -3, 4, -1, -2, 1, 5, -3};
   int n = sizeof(a)/sizeof(a[0]);
   int k = 3;
   int max_sum = maxSubArraySumKRepetition(a,n,k);
   printf("Maximum contiguous sum is %d\n", max_sum);
   return 0;
}