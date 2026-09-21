#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int calculate_perimeter(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }
    return 2 * (length + width);
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    long l = strtol(argv[1], NULL, 10);
    long w = strtol(argv[2], NULL, 10);

    if (l < 0 || l > INT_MAX || w < 0 || w > INT_MAX) {
        return EXIT_FAILURE;
    }

    int length = (int)l;
    int width = (int)w;

    int perimeter = calculate_perimeter(length, width);
    if (perimeter < 0) {
        return EXIT_FAILURE;
    }

    printf("%d\n", perimeter);

    return EXIT_SUCCESS;
}