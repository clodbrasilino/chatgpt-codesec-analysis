#include <stdio.h>
#include <math.h>

int countOddFactors(int low, int high) {
    if (low > high || low < 0) {
        return 0;
    }
    
    int count = 0;
    int start = (int)ceil(sqrt(low));
    int end = (int)floor(sqrt(high));
    
    count = end - start + 1;
    return count;
}

int main() {
    int low = 1;
    int high = 100;
    
    int result = countOddFactors(low, high);
    printf("%d\n", result);
    
    low = 10;
    high = 20;
    result = countOddFactors(low, high);
    printf("%d\n", result);
    
    return 0;
}