#include <stdio.h>

int countBinarySequences(int n) {
    if (n <= 0) {
        return 0;
    }

    int count = 0;

    for (int i = 0; i <= (1 << (2 * n)); i++) {
        int firstHalfSum = 0;
        int secondHalfSum = 0;
        
        int bitmask = i;
        for (int j = 0; j < 2 * n; j++) {
            if (bitmask & 1) {
                if (j < n) {
                    firstHalfSum++;
                } else {
                    secondHalfSum++;
                }
            }
            bitmask >>= 1;
        }

        if (firstHalfSum == secondHalfSum) {
            count++;
        }
    }

    return count;
}

int main() {
    int n;
    printf("Enter a value for n: ");
    scanf("%d", &n);

    int result = countBinarySequences(n);
    printf("Count of binary sequences of length 2n: %d\n", result);

    return 0;
}