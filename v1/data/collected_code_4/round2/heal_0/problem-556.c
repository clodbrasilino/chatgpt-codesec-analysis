#include <stdio.h>

int countOddXorPairs(int arr[], int n) 
{ 
    int i, even_count = 0, result = 0; 
 
    for (i = 0; i < n; i++)        
        if (arr[i] % 2 == 0) 
            even_count++; 
  
    result = n - even_count; 
  
    return (even_count * result); 
} 
  
int main() 
{ 
    int arr[] = {2,4,6,8}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    printf("%d", countOddXorPairs(arr, n)); 
    return 0; 
}