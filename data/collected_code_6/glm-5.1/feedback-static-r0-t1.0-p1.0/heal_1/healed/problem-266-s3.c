#include <stdio.h>

int main() {
    int side;
    if (scanf("%d", &side) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (side < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int area = 4 * side * side;
    if (area < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("%d\n", area);
    return 0;
}