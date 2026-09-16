#include <stdio.h>

int eulerian_number(int n, int m) {
    if (n == 0 || m >= n || m < 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return ((n - m) * eulerian_number(n - 1, m - 1) + (m + 1) * eulerian_number(n - 1, m));
}

int main() {
    int n = 4;
    int m = 2;
    int result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is: %d\n", n, m, result);
    return 0;
}