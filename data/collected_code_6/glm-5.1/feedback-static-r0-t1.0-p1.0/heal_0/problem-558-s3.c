#include <stdio.h>
#include <stdlib.h>

int digit_distance(int a, int b) {
    int dist = 0;
    unsigned int ua;
    unsigned int ub;

    ua = (a < 0) ? (unsigned int)(-(long long)a) : (unsigned int)a;
    ub = (b < 0) ? (unsigned int)(-(long long)b) : (unsigned int)b;

    if (ua == 0 && ub == 0) {
        return 0;
    }

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
    int x, y;
    if (scanf("%d %d", &x, &y) == 2) {
        printf("%d\n", digit_distance(x, y));
    }
    return 0;
}