#include <stdio.h>
#include <stdlib.h>

int countOddSetBits(int *arr, size_t size) {
    if (arr == NULL) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned int n = (unsigned int)arr[i];
        int setBits = 0;
        while (n > 0) {
            setBits += n & 1;
            n >>= 1;
        }
        if (setBits % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {2, 3, 5, 7, 8, 11};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    int result = countOddSetBits(arr, size);
    
    printf("%d\n", result);
    
    return 0;
}