#include <stdio.h>
#include <stdlib.h>

int digit_distance(int a, int b) {
    int dist = 0;
    unsigned int ua = (unsigned int)(a < 0 ? -a : a);
    unsigned int ub = (unsigned int)(b < 0 ? -b : b);

    while (ua > 0 || ub > 0) {
        int da = ua % 10;
        int db = ub % 10;
        dist += abs(da - db);
        ua /= 10;
        ub /= 10;
    }

    return dist;
}

int main(void) {
    int x = 123;
    int y = 456;
    int result = digit_distance(x, y);
    printf("%d\n", result);
    return 0;
}