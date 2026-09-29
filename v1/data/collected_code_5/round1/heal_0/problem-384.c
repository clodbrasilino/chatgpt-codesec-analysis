#include <stdio.h>
#include <limits.h>

int find_freq_smallest(int arr[], int n){
    int freq = 0, min = INT_MAX;
    for(int i = 0; i < n; i++){
        if(arr[i] < min){
            min = arr[i];
            freq = 1;
        } else if (arr[i] == min) {
            freq++;
        }
    }
    return freq;
}

int main() {
    int arr[] = {2, 5, 3, 2, 5, 3, 2, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    int freq = find_freq_smallest(arr, n);

    if(freq == 0)
    {
        printf("Array is empty");
    }
    else
    {
        printf("Frequency of the smallest integer is: %d", freq);
    }
    return 0;
}
