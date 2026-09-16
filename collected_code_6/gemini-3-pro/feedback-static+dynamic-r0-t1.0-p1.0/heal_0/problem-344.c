#include <stdio.h>
#include <math.h>

int countOddFactors(int start, int end) {
    if (start > end || start < 0) {
        return 0;
    }

    int start_sqrt = (int)ceil(sqrt(start));
    int end_sqrt = (int)floor(sqrt(end));

    if (start_sqrt > end_sqrt) {
        return 0;
    }

    return (end_sqrt - start_sqrt) + 1;
}

int main(void) {
    int start = 1;
    int end = 100;
    
    int result = countOddFactors(start, end);
    
    printf("%d\n", result);
    
    return 0;
}