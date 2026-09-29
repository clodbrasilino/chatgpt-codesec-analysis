#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_segments(int n, int a, int b, int c) {
    int max = 0;
    for (int i = 0; i <= n / a; ++i) {
        for (int j = 0; j <= (n - i * a) / b; ++j) {
            int k = (n - i * a - j * b) / c;
            if (i * a + j * b + k * c == n && i + j + k > max) {
                max = i + j + k;
            }
        }
    }
    return max;
}

int main() {
    int n, a, b, c;
    printf("Enter the total length n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input for n.\n");
        return EXIT_FAILURE;
    }
    printf("Enter the segment lengths a, b, and c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3 || a <= 0 || b <= 0 || c <= 0) {
        fprintf(stderr, "Invalid input for a, b, or c.\n");
        return EXIT_FAILURE;
    }

    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);

    return 0;
}