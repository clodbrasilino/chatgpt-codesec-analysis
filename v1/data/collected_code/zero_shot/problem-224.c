#include <stdio.h>

int countSetBits(int num) {
    int count = 0;
    
    while (num != 0) {
        // Using bitwise AND operator to check if the rightmost bit is set
        if (num & 1) {
            count++;
        }
        
        // Right shifting the number by 1 position
        num = num >> 1;
    }
    
    return count;
}

int main() {
    int number = 5;
    int result = countSetBits(number);

    printf("Number of set bits: %d\n", result);

    return 0;
}