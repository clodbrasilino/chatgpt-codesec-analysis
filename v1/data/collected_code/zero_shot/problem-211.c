#include <stdio.h>

int countNumbersWithSetBits(int oth, int nth) {
    int count = 0;
    for (int i = 1; i <= 100; i++) {
        if ((i & (1 << oth)) && (i & (1 << nth)))
            count++;
    }
    return count;
}

int main() {
    int oth, nth;
    printf("Enter the value of oth and nth: ");
    scanf("%d %d", &oth, &nth);
    
    printf("Number of numbers with oth and nth bits set: %d\n", countNumbersWithSetBits(oth, nth));
    
    return 0;
}