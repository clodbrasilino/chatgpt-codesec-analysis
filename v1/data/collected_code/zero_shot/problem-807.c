#include <stdio.h>

int findFirstOdd(int numbers[], int size) {
    for(int i = 0; i < size; i++) {
        if(numbers[i] % 2 != 0) {
            return numbers[i];
        }
    }
    return -1;
}

int main() {
    int numbers[] = {2, 4, 6, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int firstOdd = findFirstOdd(numbers, size);
    
    printf("First odd number: %d", firstOdd);
    
    return 0;
}