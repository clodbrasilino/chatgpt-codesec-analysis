#include <stdio.h>

long long tetrahedralNumber(int n) {
    if (n < 1) {
        printf("Invalid input. n must be greater than or equals to 1.\n");
        return -1;
    }
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    int n;
    printf("Enter the order of tetrahedral number: ");
    scanf("%d", &n);
    long long tetrahedral = tetrahedralNumber(n);
    if (tetrahedral != -1) {
        printf("The %dth tetrahedral number is: %lld\n", n, tetrahedral);
    }
    return 0;
}