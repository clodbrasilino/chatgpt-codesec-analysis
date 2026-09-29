#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

int are_parallel(Point p1, Point p2, Point p3, Point p4) {
    double dx1 = p2.x - p1.x;
    double dy1 = p2.y - p1.y;
    double dx2 = p4.x - p3.x;
    double dy2 = p4.y - p3.y;

    double cross = dx1 * dy2 - dy1 * dx2;

    if (cross == 0.0) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 9) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3 x4 y4\n", argv[0]);
        return EXIT_FAILURE;
    }

    Point p1, p2, p3, p4;

    p1.x = strtod(argv[1], NULL);
    p1.y = strtod(argv[2], NULL);
    p2.x = strtod(argv[3], NULL);
    p2.y = strtod(argv[4], NULL);
    p3.x = strtod(argv[5], NULL);
    p3.y = strtod(argv[6], NULL);
    p4.x = strtod(argv[7], NULL);
    p4.y = strtod(argv[8], NULL);

    int result = are_parallel(p1, p2, p3, p4);

    if (result == 1) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }

    return EXIT_SUCCESS;
}