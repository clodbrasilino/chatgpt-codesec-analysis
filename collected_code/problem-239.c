#include <stdio.h>

int countSequences(int n, int m) {
    if (n == 0)
        return 1;
    int count = 0;
    for (int i = n; i >= 1; i--) {
        if (i * 2 <= m) {
            count += countSequences(n - 1, i * 2);
        }
    }
    return count;
}

int main() {
    int n = 3;
    int m = 6;
    int result = countSequences(n, m);
    printf("Number of possible sequences: %d\n", result);
    return 0;
}