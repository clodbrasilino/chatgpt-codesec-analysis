#include <stdio.h>

int find_frequency(int arr[], int size, int target) {
    int frequency = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            frequency++;
        }
    }
    
    return frequency;
}

int main(void) {
    int numbers[] = {2, 5, 9, 2, 8, 2, 7, 5, 3, 2};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int target = 2;
    
    int result = find_frequency(numbers, size, target);
    
    printf("Frequency of %d in the array: %d\n", target, result);
    
    return 0;
}