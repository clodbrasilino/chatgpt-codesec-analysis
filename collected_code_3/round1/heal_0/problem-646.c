#include <stdio.h>

long long cubeCount(int n, int k) {
    long long result = n - k + 1;
    return result * result * result;
}

int main() {
    int n, k;
    printf("Enter the size of the large cube: ");
    scanf("%d", &n);
    printf("Enter the size of the small cube: ");
    scanf("%d", &k);
    printf("Number of small cubes in the large cube: %lld\n", cubeCount(n, k));
    return 0;
}