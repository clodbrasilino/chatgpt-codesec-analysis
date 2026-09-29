#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    int max = 0;
    for (int i = 0; i * a <= n; i++) {
        for (int j = 0; i * a + j * b <= n; j++) {
            int k = (n - i * a - j * b) / c;
            if (i * a + j * b + k * c == n) {
                max = (i + j + k > max) ? i + j + k : max;
            }
        }
    }
    return max;
}

int main() {
    int n = 20, a = 2, b = 3, c = 5;
    int result = max_segments(n, a, b, c);
    printf("Maximum number of segments: %d\n", result);
    return 0;
}