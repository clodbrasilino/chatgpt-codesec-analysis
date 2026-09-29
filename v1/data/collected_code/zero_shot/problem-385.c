#include <stdio.h>

int perrin(int n) {
    if (n == 0) {
        return 3;
    }
    else if (n == 1) {
        return 0;
    }
    else if (n == 2) {
        return 2;
    }
    else {
        return perrin(n-2) + perrin(n-3);
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %d'th perrin number is: %d\n", n, perrin(n));
    return 0;
}