#include <stdio.h>

int findMaximumOccurringDivisor(int start, int end) {
    int divisorCount[100] = {0};
    
    for (int i = start; i <= end; i++) {
        for (int j = 1; j <= i; j++) {
            if (i % j == 0) {
                divisorCount[j]++;
            }
        }
    }
    
    int maxDivisor = 1;
    
    for (int i = 2; i <= end; i++) {
        if (divisorCount[i] > divisorCount[maxDivisor]) {
            maxDivisor = i;
        }
    }
    
    return maxDivisor;
}

int main() {
    int start, end;
    printf("Enter the interval start: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'start' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &start);
    printf("Enter the interval end: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'end' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &end);
    
    int result = findMaximumOccurringDivisor(start, end);
    
    printf("The maximum occurring divisor in the interval is: %d\n", result);
    
    return 0;
}