#include <stdio.h>
#define MAX_SIZE 100

void find_similar(int arr1[], int arr2[], int n, int m)
{
    for (int i = 0; i < n; i++) 
    {
      for(int j = 0; j < m; j++) 
      {
        if(arr1[i] == arr2[j]) 
        {
           printf("%d ", arr1[i]);
           break;
        }
      }
   }
}

int main()
{
   int arr1[MAX_SIZE], arr2[MAX_SIZE], n, m, i;
      
   printf("Enter size of first array : ");
   scanf("%d", &n);
   printf("Enter elements in array : ");
   for(i=0; i<n; i++)
   {
       scanf("%d", &arr1[i]);
   }
   
   printf("\nEnter size of second array : ");
   scanf("%d", &m);
   printf("Enter elements in array : ");
   for(i=0; i<m; i++)
   {
       scanf("%d", &arr2[i]);
   }
   
   find_similar(arr1,arr2,n,m);  
   return 0;
}