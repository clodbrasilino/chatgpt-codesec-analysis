#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool have_opposite_signs(int a, int b) {
    if (a == 0 || b == 0) {
        return false;
    }
    return (a > 0) != (b > 0);
}

int main(void) {
    int x, y;
    if (scanf("%d %d", &x, &y) != 2) {
        return 1;
    }
    bool result = have_opposite_signs(x, y);
    printf("%d\n", result);
    return 0;
}