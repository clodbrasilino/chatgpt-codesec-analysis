#include <stdio.h>

int countCubes(int n, int k) {
    int count = 0;
    for (int i = k; i <= n; i++) {
        count += (n - i + 1) * (n - i + 1);
    }
    return count;
}

int main() {
    int n, k;
    printf("Enter the size of the cube (n): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    printf("Enter the size of the cube to count (k): ");
    /* Possible weaknesses found:
     *  Cannot determine that 'k' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &k);
    int result = countCubes(n, k);
    printf("Number of cubes of size %d in a cube of size %d: %d\n", k, n, result);
    return 0;
}