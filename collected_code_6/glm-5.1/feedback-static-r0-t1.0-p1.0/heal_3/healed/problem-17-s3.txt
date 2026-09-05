#include <stdio.h>

int find_perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return side * 4;
}

int main() {
    int side;
    if (scanf("%d", &side) != 1) {
        return 1;
    }

    int perimeter = find_perimeter(side);

    if (perimeter == -1) {
        return 1;
    }

    printf("%d\n", perimeter);
    return 0;
}