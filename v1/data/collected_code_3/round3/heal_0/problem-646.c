#include <stdio.h>

long long countCubes(int n, int k) {
    long long total = n - k + 1;
    return total * total * total;
}

int main() {
    int n, k;
    printf("Enter the size of the larger cube: ");
    scanf("%d", &n);
    printf("Enter the size of the smaller cube: ");
    scanf("%d", &k);
    printf("Number of smaller cubes in the larger cube: %lld\n", countCubes(n, k));
    return 0;
}