#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    double area = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    double threshold = 1e-9;
    
    if (area < 0) {
        area = -area;
    }
    
    if (area < threshold) {
        return 0;
    }
    
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    double x1 = strtod(argv[1], NULL);
    double y1 = strtod(argv[2], NULL);
    double x2 = strtod(argv[3], NULL);
    double y2 = strtod(argv[4], NULL);
    double x3 = strtod(argv[5], NULL);
    double y3 = strtod(argv[6], NULL);
    
    if (is_valid_triangle(x1, y1, x2, y2, x3, y3)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return EXIT_SUCCESS;
}