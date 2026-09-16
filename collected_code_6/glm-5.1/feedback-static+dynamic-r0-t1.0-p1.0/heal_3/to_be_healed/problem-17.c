#include <stdio.h>
#include <stdlib.h>

int perimeter(int side) {
    if (side <= 0) {
        return -1;
    }
    return 4 * side;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int side;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &side) != 1) {
        return EXIT_FAILURE;
    }
    int result = perimeter(side);
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}