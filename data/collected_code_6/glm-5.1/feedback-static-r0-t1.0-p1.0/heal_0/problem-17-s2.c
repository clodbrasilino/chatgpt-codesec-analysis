#include <stdio.h>
#include <stdlib.h>

int perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return 4 * side;
}

int main(int argc, char *argv[]) {
    int side = 5;
    int result = perimeter(side);
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}