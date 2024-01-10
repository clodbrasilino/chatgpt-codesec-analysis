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
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[0] members' is initialized [premium-bughuntingUninit]
     */
    counters[0].key = 1;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[0] members' is initialized [premium-bughuntingUninit]
     */
    counters[0].value = 5;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[1] members' is initialized [premium-bughuntingUninit]
     */
    counters[1].key = 2;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[1] members' is initialized [premium-bughuntingUninit]
     */
    counters[1].value = 2;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[2] members' is initialized [premium-bughuntingUninit]
     */
    counters[2].key = 3;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[2] members' is initialized [premium-bughuntingUninit]
     */
    counters[2].value = 7;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[3] members' is initialized [premium-bughuntingUninit]
     */
    counters[3].key = 4;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[3] members' is initialized [premium-bughuntingUninit]
     */
    counters[3].value = 1;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[4] members' is initialized [premium-bughuntingUninit]
     */
    counters[4].key = 5;
    /* Possible weaknesses found:
     *  Cannot determine that 'counters[4] members' is initialized [premium-bughuntingUninit]
     */
    counters[4].value = 4;
    
    // Sort counters by value
    sortCounterByValue(counters, 5);
    
    // Print sorted counters
    for(int i=0; i<5; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'counters[i] members' is initialized [premium-bughuntingUninit]
         */
        printf("Counter %d: key=%d, value=%d\n", i+1, counters[i].key, counters[i].value);
    }
    
    return 0;
}