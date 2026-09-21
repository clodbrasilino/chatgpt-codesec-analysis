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

int main(void) {
    Line l1, l2;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};
    size_t len;

    printf("Enter coordinates for line 1 (x1 y1 x2 y2): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    if (sscanf(input, "%lf %lf %lf %lf", &l1.x1, &l1.y1, &l1.x2, &l1.y2) != 4) {
        return EXIT_FAILURE;
    }

    printf("Enter coordinates for line 2 (x1 y1 x2 y2): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    if (sscanf(input, "%lf %lf %lf %lf", &l2.x1, &l2.y1, &l2.x2, &l2.y2) != 4) {
        return EXIT_FAILURE;
    }

    if (are_parallel(l1, l2)) {
        printf("Lines are parallel\n");
    } else {
        printf("Lines are not parallel\n");
    }

    return EXIT_SUCCESS;
}