#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canBeRepresentedAsDifferenceOfSquares(int n) {
    if (n < 0) {
        n = -n;
    }
    
    if (n % 4 == 2) {
        return false;
    }
    return true;
}

int main(void) {
    int num = 0;
    
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (canBeRepresentedAsDifferenceOfSquares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return EXIT_SUCCESS;
}