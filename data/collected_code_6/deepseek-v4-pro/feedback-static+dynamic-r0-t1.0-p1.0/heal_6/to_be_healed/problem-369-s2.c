#include <stdio.h>
#include <stdlib.h>

double lateral_surface_area_cuboid(double length, double width, double height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        fprintf(stderr, "Error: Dimensions must be positive numbers\n");
        return -1;
    }
    return 2 * height * (length + width);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double length, width, height, area;

    if (argc != 4) {
        printf("Usage: %s <length> <width> <height>\n", argv[0]);
        printf("Example: %s 10 5 3\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;
    length = strtod(argv[1], &endptr1);
    width = strtod(argv[2], &endptr2);
    height = strtod(argv[3], &endptr3);

    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        fprintf(stderr, "Error: Invalid numeric input\n");
        return EXIT_FAILURE;
    }

    area = lateral_surface_area_cuboid(length, width, height);
    
    if (area < 0) {
        return EXIT_FAILURE;
    }

    printf("Lateral Surface Area of Cuboid: %.2f\n", area);
    return EXIT_SUCCESS;
}