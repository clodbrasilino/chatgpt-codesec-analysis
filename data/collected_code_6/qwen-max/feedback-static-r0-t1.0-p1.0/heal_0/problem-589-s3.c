#include <stdio.h>
#include <math.h>

int isPerfectSquare(int n) {
    int root = sqrt(n);
    return root * root == n;
}

void findPerfectSquaresInRange(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (isPerfectSquare(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int start = 1;
    int end = 100;
    findPerfectSquaresInRange(start, end);
    return 0;
}