#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_integral_coordinates(int x1, int y1, int x2, int y2) {
    int min_x = x1 < x2 ? x1 : x2;
    int max_x = x1 < x2 ? x2 : x1;
    int min_y = y1 < y2 ? y1 : y2;
    int max_y = y1 < y2 ? y2 : y1;

    if (max_x - min_x <= 1 || max_y - min_y <= 1) {
        return 0;
    }

    return (max_x - min_x - 1) * (max_y - min_y - 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 5) {
        return EXIT_FAILURE;
    }

    long val1 = strtol(argv[1], NULL, 10);
    long val2 = strtol(argv[2], NULL, 10);
    long val3 = strtol(argv[3], NULL, 10);
    long val4 = strtol(argv[4], NULL, 10);

    if (val1 < INT_MIN || val1 > INT_MAX || 
        val2 < INT_MIN || val2 > INT_MAX || 
        val3 < INT_MIN || val3 > INT_MAX || 
        val4 < INT_MIN || val4 > INT_MAX) {
        return EXIT_FAILURE;
    }

    int x1 = (int)val1;
    int y1 = (int)val2;
    int x2 = (int)val3;
    int y2 = (int)val4;

    int count = count_integral_coordinates(x1, y1, x2, y2);
    printf("%d\n", count);

    return EXIT_SUCCESS;
}