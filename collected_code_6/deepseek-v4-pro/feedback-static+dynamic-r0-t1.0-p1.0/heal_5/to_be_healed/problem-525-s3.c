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

static void flush_stdin(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF);
}

static int read_line_input(const char *prompt, Line *line) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[512];
    size_t len;
    size_t input_len;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    input_len = sizeof(input);
    len = 0;
    while (len < input_len && input[len] != '\0') {
        len++;
    }
    if (len >= input_len) {
        flush_stdin();
        return 0;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        flush_stdin();
    }

    if (sscanf(input, "%lf %lf %lf %lf", &line->x1, &line->y1, &line->x2, &line->y2) != 4) {
        return 0;
    }

    return 1;
}

int main(void) {
    Line l1, l2;

    if (!read_line_input("Enter coordinates for line 1 (x1 y1 x2 y2): ", &l1)) {
        return EXIT_FAILURE;
    }

    if (!read_line_input("Enter coordinates for line 2 (x1 y1 x2 y2): ", &l2)) {
        return EXIT_FAILURE;
    }

    if (are_parallel(l1, l2)) {
        printf("Lines are parallel\n");
    } else {
        printf("Lines are not parallel\n");
    }

    return EXIT_SUCCESS;
}