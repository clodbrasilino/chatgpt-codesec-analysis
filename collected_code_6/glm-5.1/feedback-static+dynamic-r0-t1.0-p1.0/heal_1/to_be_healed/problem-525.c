#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Line;

int are_parallel(Line l1, Line l2) {
    double dx1 = l1.p2.x - l1.p1.x;
    double dy1 = l1.p2.y - l1.p1.y;
    double dx2 = l2.p2.x - l2.p1.x;
    double dy2 = l2.p2.y - l2.p1.y;

    if (dx1 == 0.0 && dx2 == 0.0) {
        return 1;
    }
    if (dx1 == 0.0 || dx2 == 0.0) {
        return 0;
    }
    return dy1 * dx2 == dy2 * dx1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 9) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3 x4 y4\n", argv[0]);
        return EXIT_FAILURE;
    }

    Line l1, l2;

    l1.p1.x = strtod(argv[1], NULL);
    l1.p1.y = strtod(argv[2], NULL);
    l1.p2.x = strtod(argv[3], NULL);
    l1.p2.y = strtod(argv[4], NULL);

    l2.p1.x = strtod(argv[5], NULL);
    l2.p1.y = strtod(argv[6], NULL);
    l2.p2.x = strtod(argv[7], NULL);
    l2.p2.y = strtod(argv[8], NULL);

    if (are_parallel(l1, l2)) {
        printf("Parallel\n");
    } else {
        printf("Not parallel\n");
    }

    return EXIT_SUCCESS;
}