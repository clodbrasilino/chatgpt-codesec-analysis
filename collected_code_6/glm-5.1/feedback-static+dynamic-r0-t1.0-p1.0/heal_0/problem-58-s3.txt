#include <stdio.h>
#include <stdbool.h>

bool have_opposite_sign(int a, int b) {
    return (a ^ b) < 0;
}

int main(void) {
    int x, y;
    if (scanf("%d %d", &x, &y) != 2) {
        return 1;
    }
    printf("%d\n", have_opposite_sign(x, y));
    return 0;
}