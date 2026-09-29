#include <stdio.h>

int findMaxSegments(int a, int b, int c, int n) {
    int maxSegments = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            int k = n - (a * i + b * j);
            if (k >= 0 && k % c == 0) {
                int segments = i + j + k / c;
                if (segments > maxSegments) {
                    maxSegments = segments;
                }
            }
        }
    }
    return maxSegments;
}

int main() {
    int a = 0, b = 0, c = 0, n = 0;

    printf("Enter the lengths a, b, c, and n: \n");

    if (scanf("%d %d %d %d", &a, &b, &c, &n) != 4) {
        printf("Invalid input!\n");
        return 1;
    }

    int maxSegments = findMaxSegments(a, b, c, n);
    printf("The maximum number of segments of lengths a, b, and c that can be formed from n is: %d\n", maxSegments);
    return 0;
}