#include <stdio.h>

// Function to find frequency count of list of lists 
int findFrequency(int arr[], int n) 
{ 
    // Initialize frequency count array with all zeros 
    int freq[n]; 
    for (int i = 0; i < n; i++) 
        freq[i] = 0; 
  
    // Loop through the array and update frequency count 
    for (int i = 0; i < n; i++) 
        freq[arr[i]]++; 
  
    // Print frequency count of each element 
    for (int i = 0; i < n; i++) { 
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