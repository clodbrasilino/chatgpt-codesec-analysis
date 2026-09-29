#include <stdio.h>
#include <math.h>

int countOddFactorsInRange(int start, int end) {
    if (start > end) {
        return 0;
    }

    if (start < 1) {
        start = 1;
    }
    
    if (end < 1) {
        return 0;
    }

    int count = 0;
    
    long long sqrt_start = (long long)sqrt((double)start);
    long long sqrt_end = (long long)sqrt((double)end);

    while (sqrt_start * sqrt_start < start) {
        sqrt_start++;
    }
    
    while (sqrt_start * sqrt_start > start) {
        sqrt_start--;
    }

    for (long long i = sqrt_start; i <= sqrt_end; i++) {
        if (i * i >= start && i * i <= end) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int start, end;

    if (scanf("%d %d", &start, &end) != 2) {
        return 1;
    }

    printf("%d\n", countOddFactorsInRange(start, end));

    return 0;
}