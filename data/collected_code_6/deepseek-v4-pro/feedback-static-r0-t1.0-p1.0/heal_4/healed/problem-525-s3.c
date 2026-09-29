#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    double x1, y1, x2, y2;
} Line;

int are_parallel(Line l1, Line l2) {
    double dx1 = l1.x2 - l1.x1;
    double dy1 = l1.y2 - l1.y1;
    double dx2 = l2.x2 - l2.x1;
    double dy2 = l2.y2 - l2.y1;

    if ((fabs(dx1) < 1e-10 && fabs(dy1) < 1e-10) ||
        (fabs(dx2) < 1e-10 && fabs(dy2) < 1e-10)) {
        return 0;
    }

    double cross = dx1 * dy2 - dy1 * dx2;
    return fabs(cross) < 1e-10;
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_line_coordinates(Line *line, int line_number) {
    char input[256];
    size_t len;
    size_t i;

    for (i = 0; i < sizeof(input); i++) {
        input[i] = '\0';
    }

    printf("Enter coordinates for line %d (x1 y1 x2 y2): ", line_number);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }

    if (len >= sizeof(input)) {
        input[sizeof(input) - 1] = '\0';
    }

    if (len > 0 && input[len - 1] != '\n') {
        clear_input_buffer();
    } else if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (sscanf(input, "%lf %lf %lf %lf", 
               &line->x1, &line->y1, &line->x2, &line->y2) != 4) {
        return 0;
    }

    return 1;
}

int main(void) {
    Line l1;
    Line l2;

    if (!read_line_coordinates(&l1, 1)) {
        return EXIT_FAILURE;
    }

    if (!read_line_coordinates(&l2, 2)) {
        return EXIT_FAILURE;
    }

    if (are_parallel(l1, l2)) {
        printf("Lines are parallel\n");
    } else {
        printf("Lines are not parallel\n");
    }

    return EXIT_SUCCESS;
}