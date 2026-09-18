#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int countEquilateralTriangles(int n) {
    if (n < 3) return 0;
    long long count = 0;
    for (int size = 1; size <= n; ++size) {
        int layers = n - size + 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9222160285916505066 + 12345512988212496 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:657,execs:288,op:havoc,rep:6)
         */
        count += (long long)layers * layers;
    }
    return (int)(count > INT_MAX ? INT_MAX : count);
}

int main() {
    int n;
    printf("Enter the size of the equilateral triangle: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    int result = countEquilateralTriangles(n);
    printf("Maximum number of equilateral triangles: %d\n", result);
    return 0;
}