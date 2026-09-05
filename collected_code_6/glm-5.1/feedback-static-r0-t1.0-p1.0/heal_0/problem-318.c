#include <stdio.h>

long long find_max_cuboid_volume(long long s) {
    if (s <= 0) {
        return -1;
    }
    if (s % 3 == 0) {
        long long side = s / 3;
        return side * side * side;
    }
    if (s % 3 == 1) {
        long long side1 = (s - 4) / 3;
        long long side2 = side1 + 1;
        if (side1 < 1) {
            return -1;
        }
        return side1 * side1 * side2;
    }
    if (s % 3 == 2) {
        long long side = (s - 2) / 3;
        if (side < 1) {
            return -1;
        }
        return side * side * (side + 1);
    }
    return -1;
}

int main(void) {
    long long s;
    if (scanf("%lld", &s) != 1) {
        return 1;
    }
    long long volume = find_max_cuboid_volume(s);
    printf("%lld\n", volume);
    return 0;
}