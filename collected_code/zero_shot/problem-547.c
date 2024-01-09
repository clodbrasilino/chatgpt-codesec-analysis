#include <stdio.h>

int hammingDistance(int x, int y) {
    int result = 0;
    int xor = x ^ y;
    
    while (xor > 0) {
        if (xor & 1) {
            result++;
        }
        xor = xor >> 1;
    }
    
    return result;
}

int consecutiveHammingDistance(int n) {
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum += hammingDistance(i, i+1);
    }
    
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    
    int result = consecutiveHammingDistance(n);
    printf("Sum of hamming distances: %d\n", result);
    
    return 0;
}