#include <stdio.h>

int countCubes(int n, int k) {
    int count = 0;
    for (int i = k; i <= n; i++) {
        count += (n - i + 1) * (n - i + 1);
    }
    return count;
}

int main() {
    int n = 0, k = 0;
    printf("Enter the size of the cube (n): ");
    scanf("%d", &n);
    printf("Enter the size of the cube to count (k): ");
    scanf("%d", &k);
    int result = countCubes(n, k);
    printf("Number of cubes of size %d in a cube of size %d: %d\n", k, n, result);
    return 0;
}