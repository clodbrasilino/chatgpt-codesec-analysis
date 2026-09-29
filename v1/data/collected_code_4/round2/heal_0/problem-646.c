#include <stdio.h>

long long cube_count(int n, int k) {
    if (n < k) {
        printf("Error: The provided input is invalid.\n");
        return -1;
    }
    long long diff = n - k + 1;
    return diff * diff * diff;
}

int main() {
    int n, k;

    printf("Enter the size of the larger cube: ");
    scanf("%d", &n);

    printf("Enter the size of the smaller cube: ");
    scanf("%d", &k);

    long long result = cube_count(n, k);

    if(result == -1) {
        printf("The provided input is invalid.\n");
    } else {
        printf("Number of cubes of size %d in a cube of size %d: %lld\n", k, n, result);
    }

    return 0;
}