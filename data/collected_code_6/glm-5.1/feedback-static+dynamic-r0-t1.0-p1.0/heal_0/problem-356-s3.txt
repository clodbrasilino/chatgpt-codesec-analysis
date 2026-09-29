#include <stdio.h>
#include <stdlib.h>

int find_third_angle(int a, int b) {
    if (a <= 0 || b <= 0 || (a + b) >= 180) {
        exit(EXIT_FAILURE);
    }
    return 180 - a - b;
}

int main(int argc, char *argv[]) {
    int a, b, c;
    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }
    c = find_third_angle(a, b);
    printf("%d\n", c);
    return EXIT_SUCCESS;
}