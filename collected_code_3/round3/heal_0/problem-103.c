#include <stdio.h>

int eulerian(int n, int m) {
    if (m >= n || n == 0)
        return 0;
    if (m == 0 || m == n - 1)
        return 1;
    return (n - m) * eulerian(n - 1, m - 1) + (m + 1) * eulerian(n - 1, m);
}

int main() {
    int n, m;
    printf("Enter n and m: ");
    scanf("%d %d", &n, &m);
    printf("Eulerian number is: %d\n", eulerian(n, m));
    return 0;
}