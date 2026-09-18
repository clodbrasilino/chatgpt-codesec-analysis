#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void findPerfectSquares(int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (i > 0 && i < INT_MAX) {
            int sqrtVal = (int)sqrt((double)i);
            if (sqrtVal * sqrtVal == i) {
                printf("%d ", i);
            }
        }
    }
    printf("\n");
}

int main() {
    int start, end;
    printf("Enter the starting number: ");
    if (scanf("%d", &start) != 1 || start < 0) {
        fprintf(stderr, "Invalid starting number.\n");
        return EXIT_FAILURE;
    }
    printf("Enter the ending number: ");
    if (scanf("%d", &end) != 1 || end < 0) {
        fprintf(stderr, "Invalid ending number.\n");
        return EXIT_FAILURE;
    }

    if (start > end) {
        fprintf(stderr, "Starting number must be less than or equal to the ending number.\n");
        return EXIT_FAILURE;
    }

    findPerfectSquares(start, end);

    return EXIT_SUCCESS;
}