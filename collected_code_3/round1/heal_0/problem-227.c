#include <stdio.h>

int find_min(int a, int b, int c) {
    int min = a;

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }

    return min;
}

int main() {
    int a, b, c;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);

    printf("Minimum: %d\n", find_min(a, b, c));

    return 0;
}