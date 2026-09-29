#include <stdio.h>

int maxOccuringDivisor(int start, int end) {
    int maxDivisor = 0;
    int maxCount = 0;
    int i, j, count;

    for(i = start; i <= end; i++) {
        count = 0;
        for(j = 1; j <= i; j++) {
            if(i % j == 0) {
                count++;
            }
        }
        if(count > maxCount) {
            maxCount = count;
            maxDivisor = i;
        }
    }
    return maxDivisor;
}

int main() {
    int start, end;
    printf("Enter the start of the interval: ");
    scanf("%d", &start);
    printf("Enter the end of the interval: ");
    scanf("%d", &end);
    printf("The number with maximum divisors in the given interval is: %d\n", maxOccuringDivisor(start, end));
    return 0;
}