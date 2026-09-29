#include<stdio.h>

// Structure to store counter key-value pairs
struct counter {
    int key;
    int value;
};

// Function to sort counter by value
void sortCounterByValue(struct counter *arr, int n) {
    // Insertion sort algorithm
    for(int i=1; i<n; i++) {
        struct counter temp = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j].value < temp.value) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

int main() {
    // Example usage of sortCounterByValue function
    
    // Array of counter structures
    struct counter counters[5];
    
    // Initialize counters
    counters[0].key = 1;
    counters[0].value = 5;
    counters[1].key = 2;
    counters[1].value = 2;
    counters[2].key = 3;
    counters[2].value = 7;
    counters[3].key = 4;
    counters[3].value = 1;
    counters[4].key = 5;
    counters[4].value = 4;
    
    // Sort counters by value
    sortCounterByValue(counters, 5);
    
    // Print sorted counters
    for(int i=0; i<5; i++) {
        printf("Counter %d: key=%d, value=%d\n", i+1, counters[i].key, counters[i].value);
    }
    
    return 0;
}