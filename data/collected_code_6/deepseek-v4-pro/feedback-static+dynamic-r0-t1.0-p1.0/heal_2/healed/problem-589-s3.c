#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

void findPerfectSquares(int start, int end) {
    if (start > end) {
        printf("Invalid range\n");
        return;
    }

    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        printf("No perfect squares found\n");
        return;
    }

    double sqrt_start = sqrt((double)start);
    double sqrt_end = sqrt((double)end);
    
    int first = (int)ceil(sqrt_start);
    int last = (int)floor(sqrt_end);
    int found = 0;

    for (int i = first; i <= last; i++) {
        if (i < 0) {
            break;
        }
        if (i > 46340) {
            break;
        }
        int square = i * i;
        if (square >= start && square <= end) {
            if (found) {
                printf(" ");
            }
            printf("%d", square);
            found = 1;
        }
    }

    if (!found) {
        printf("No perfect squares found");
    }
    printf("\n");
}

int main(void) {
    int num1, num2;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    findPerfectSquares(num1, num2);

    return 0;
}