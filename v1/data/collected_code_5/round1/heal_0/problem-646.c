#include <stdio.h>

long long countCubes(long long n, long long k) {
   
    if(k > n || k <= 0 || n <= 0) return 0;

    return (n - k + 1) * (n - k + 1) * (n - k + 1);
}

int main() {
    long long n, k;

    printf("Enter cube size: ");
    if(scanf("%lld", &n) != 1) {
        printf("Invalid input for cube size! Please enter a positive integer.\n");
        return 1;
    }

    printf("Enter small cube size: ");
    if(scanf("%lld", &k) != 1) {
        printf("Invalid input for small cube size! Please enter a positive integer.\n");
        return 1;
    }
   
    long long res = countCubes(n, k);
    if(res == 0) {
        printf("Invalid relationship between cube size (%lld) and small cube size (%lld).\n", n, k);
        return 1;
    }

    printf("Number of cubes of size %lld in a cube of size %lld: %lld\n", k, n, res);
   
    return 0;
}