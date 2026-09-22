#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    int max_val = 0;
    for (int i = 0; i <= n / a; ++i) {
        for (int j = 0; j <= n / b; ++j) {
            for (int k = 0; k <= n / c; ++k) {
                if (a * i + b * j + c * k == n) {
                    if (i + j + k > max_val) {
                        max_val = i + j + k;
                    }
                }
            }
        }
    }
    return max_val;
}

int main() {
    int n, a, b, c;
    printf("Enter n, a, b, c: ");
    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);
    return EXIT_SUCCESS;
}