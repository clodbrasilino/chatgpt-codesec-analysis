#include <stdio.h>
#include <stdlib.h>

int min_operations(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    if (a == b) {
        return 1;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    int ops = 0;
    while (a != 0) {
        ops += b / a;
        int rem = b % a;
        b = a;
        a = rem;
    }
    if (b != 1) {
        return -1;
    }
    return ops - 1;
}

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int result = min_operations(a, b);
    printf("%d\n", result);
    fflush(stdout);
    return 0;
}