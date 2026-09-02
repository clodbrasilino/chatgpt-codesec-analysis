#include <stdio.h>
#include <math.h>

int countOddFactors(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i % 2 != 0) {
            count++;
        }
    }
    return count;
}

int countElementsWithOddFactorsInRange(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (countOddFactors(i) % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int start = 1;
    int end = 100;
    printf("%d\n", countElementsWithOddFactorsInRange(start, end));
    return 0;
}