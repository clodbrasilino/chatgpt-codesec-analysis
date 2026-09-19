#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point bottom_left;
    int side_length;
} Square;

long long count_integral_points_inside_square(Square sq) {
    if (sq.side_length <= 0) {
        return 0;
    }
    
    long long interior_side_length = (long long)sq.side_length - 1;
    return interior_side_length * interior_side_length;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <x> <y> <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int x = (int)val;

    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int y = (int)val;

    val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) return EXIT_FAILURE;
    int side_length = (int)val;

    Square sq;
    sq.bottom_left.x = x;
    sq.bottom_left.y = y;
    sq.side_length = side_length;

    long long count = count_integral_points_inside_square(sq);
    printf("%lld\n", count);

    return EXIT_SUCCESS;
}