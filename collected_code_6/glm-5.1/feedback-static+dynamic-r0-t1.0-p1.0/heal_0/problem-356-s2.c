#include <stdio.h>
#include <stdlib.h>

int find_third_angle(int a, int b) {
    if (a <= 0 || b <= 0 || (a + b) >= 180) {
        exit(EXIT_FAILURE);
    }
    return 180 - a - b;
}

int main(void) {
    int a = 50;
    int b = 60;
    int c = find_third_angle(a, b);
    printf("%d\n", c);
    return 0;
}