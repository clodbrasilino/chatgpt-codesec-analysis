#include <stdio.h>
#include <stdlib.h>

long long find_max_cuboid_volume(long long s) {
    if (s <= 0) {
        return 0;
    }
    if (s % 3 == 0) {
        long long side = s / 3;
        return side * side * side;
    }
    long long side1 = s / 3;
    long long side2 = side1;
    long long side3 = s - side1 - side2;
    long long volume1 = side1 * side2 * side3;
    
    side1 = s / 3;
    side2 = s / 3 + 1;
    side3 = s - side1 - side2;
    long long volume2 = side1 * side2 * side3;
    
    side1 = s / 3 + 1;
    side2 = s / 3 + 1;
    side3 = s - side1 - side2;
    if (side3 <= 0) {
        return volume1 > volume2 ? volume1 : volume2;
    }
    long long volume3 = side1 * side2 * side3;
    
    long long max_volume = volume1;
    if (volume2 > max_volume) {
        max_volume = volume2;
    }
    if (volume3 > max_volume) {
        max_volume = volume3;
    }
    return max_volume;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sum_of_sides>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long s = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || s < 0) {
        fprintf(stderr, "Error: Invalid input. Must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long volume = find_max_cuboid_volume(s);
    printf("%lld\n", volume);
    return EXIT_SUCCESS;
}