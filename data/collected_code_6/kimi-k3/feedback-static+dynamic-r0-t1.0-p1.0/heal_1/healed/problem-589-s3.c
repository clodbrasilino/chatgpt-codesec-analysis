#include <stdio.h>
#include <math.h>
#include <limits.h>

void findPerfectSquares(int start, int end) {
    int i;
    int sqrtStart;
    int sqrtEnd;
    
    if (start < 0) {
        sqrtStart = 0;
    } else {
        sqrtStart = (int)sqrt((double)start);
        if (sqrtStart > 0 && sqrtStart * sqrtStart > start) {
            sqrtStart--;
        } else if ((sqrtStart + 1) * (sqrtStart + 1) <= start) {
            sqrtStart++;
        }
    }
    
    if (end < 0) {
        return;
    }
    
    sqrtEnd = (int)sqrt((double)end);
    if (sqrtEnd > 0 && sqrtEnd * sqrtEnd > end) {
        sqrtEnd--;
    } else if ((sqrtEnd + 1) * (sqrtEnd + 1) <= end) {
        sqrtEnd++;
    }
    
    for (i = sqrtStart; i <= sqrtEnd; i++) {
        if (i > 0 && i > INT_MAX / i) {
            break;
        }
        printf("%d ", i * i);
    }
    printf("\n");
}

int main() {
    int start, end;
    
    printf("Enter the starting number: ");
    if (scanf("%d", &start) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter the ending number: ");
    if (scanf("%d", &end) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (start > end) {
        printf("Invalid range\n");
        return 1;
    }
    
    printf("Perfect squares between %d and %d: ", start, end);
    findPerfectSquares(start, end);
    
    return 0;
}