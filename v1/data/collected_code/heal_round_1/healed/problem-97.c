#include <stdio.h>

int findFrequency(const int arr[], int n) 
{ 
    int freq[10] = {0}; 
  
    for (int i = 0; i < n; i++) 
        freq[arr[i]]++; 
  
    for (int i = 0; i < 10; i++) { 
        if (freq[i] != 0) 
            printf("[%d] => %d\n", i, freq[i]); 
    } 
} 

int main() 
{ 
    int arr[] = {1, 2, 1, 2, 3, 1, 3, 4, 5, 4, 4}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    findFrequency(arr, n); 
    return 0; 
}