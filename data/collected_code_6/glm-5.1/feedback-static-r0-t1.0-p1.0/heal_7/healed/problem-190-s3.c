#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Point;

long long count_integral_points_inside_square(Point p1, Point p2) {
    long long x_min = (long long)p1.x < p2.x ? p1.x : p2.x;
    long long x_max = (long long)p1.x > p2.x ? p1.x : p2.x;
    long long y_min = (long long)p1.y < p2.y ? p1.y : p2.y;
    long long y_max = (long long)p1.y > p2.y ? p1.y : p2.y;

    long long length = x_max - x_min;
    long long width = y_max - y_min;

    if (length < 2 || width < 2 || length != width) {
        return 0;
    }

    long long inner_length = length - 1;

    return inner_length * inner_length;
}

int main(int argc, char * const argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <x1> <y1> <x2> <y2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val;

    val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int x1 = (int)val;

    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int y1 = (int)val;

    val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int x2 = (int)val;

    val = strtol(argv[4], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int y2 = (int)val;

    Point p1 = {x1, y1};
    Point p2 = {x2, y2};

    long long result = count_integral_points_inside_square(p1, p2);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}