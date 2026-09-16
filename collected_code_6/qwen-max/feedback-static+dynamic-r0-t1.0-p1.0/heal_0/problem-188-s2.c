#include <stdio.h>
#include <math.h>

int isPerfectSquare(int n) {
    int root = sqrt(n);
    return root * root == n;
}

int canBeRepresentedByProductOfTwoSquares(int num) {
    if (num < 0) {
        return 0;
    }
    for (int i = 1; i * i <= num; ++i) {
        if (num % (i * i) == 0) {
            int quotient = num / (i * i);
            if (isPerfectSquare(quotient)) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int num;
    scanf("%d", &num);
    if (canBeRepresentedByProductOfTwoSquares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}