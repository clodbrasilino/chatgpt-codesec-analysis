#include <stdio.h>
#include <stdlib.h>

int find_nth_non_multiple(int n, int k) {
    if (n <= 0 || k == 0) {
        exit(EXIT_FAILURE);
    }
    if (k == 1) {
        exit(EXIT_FAILURE);
    }
    int full_cycles = (n - 1) / (k - 1);
    int remainder = (n - 1) % (k - 1);
    return full_cycles * k + remainder + 1;
}

int main(void) {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    int result = find_nth_non_multiple(n, k);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}