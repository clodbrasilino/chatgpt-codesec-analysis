#include <stdio.h>

long long cubeCount(int n, int k) {
    long long diff = n - k + 1;
    return diff * diff * diff;
}

int main() {
    int n, k;
    printf("Enter the size of the large cube: ");
    scanf("%d", &n);
    printf("Enter the size of the small cube: ");
    scanf("%d", &k);
    printf("Number of small cubes in large cube: %lld\n", cubeCount(n, k));
    return 0;
}