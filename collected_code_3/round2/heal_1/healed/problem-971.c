#include <stdio.h>

int max(int a, int b, int c);

int maxSegments(int n, int a, int b, int c);

int max(int a, int b, int c) {
    if (a >= b && a >= c)
        return a;
    else if (b >= a && b >= c)
        return b;
    else
        return c;
}

int maxSegments(int n, int a, int b, int c) {
    if (n == 0)
        return 0;
    if (n < 0)
        return -1;
    
    int res = max(maxSegments(n-a, a, b, c), maxSegments(n-b, a, b, c), maxSegments(n-c, a, b, c));
    if (res == -1)
        return -1;
    return res + 1;
}

int main() {
    int n, a, b, c;
    printf("Enter the total length: ");
    scanf("%d", &n);
    printf("Enter the lengths of the segments: ");
    scanf("%d %d %d", &a, &b, &c);
    int result = maxSegments(n, a, b, c);
    if (result == -1)
        printf("It is not possible to form segments of the given lengths from the total length.\n");
    else
        printf("The maximum number of segments that can be formed is %d.\n", result);
    return 0;
}