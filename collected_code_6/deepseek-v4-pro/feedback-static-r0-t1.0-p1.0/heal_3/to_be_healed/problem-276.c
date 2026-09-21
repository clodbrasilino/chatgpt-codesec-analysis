#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>

double cylinder_volume(double radius, double height) {
    if (radius <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

double safe_strtod(const char *str) {
    char *endptr;
    double val;

    errno = 0;
    val = strtod(str, &endptr);

    if (endptr == str) {
        return -1.0;
    }

    if (errno == ERANGE && (val == HUGE_VAL || val == -HUGE_VAL || val == 0.0)) {
        return -1.0;
    }

    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\n' && *endptr != '\t') {
            return -1.0;
        }
        endptr++;
    }

    if (val < 0.0 || val > DBL_MAX) {
        return -1.0;
    }

    return val;
}

int main(void) {
    double radius, height, volume;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    size_t len;

    printf("Enter radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    if (len == 0) {
        printf("Error: Invalid input.\n");
        return 1;
    }
    radius = safe_strtod(input);
    if (radius < 0.0) {
        printf("Error: Invalid radius value.\n");
        return 1;
    }

    printf("Enter height: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    if (len == 0) {
        printf("Error: Invalid input.\n");
        return 1;
    }
    height = safe_strtod(input);
    if (height < 0.0) {
        printf("Error: Invalid height value.\n");
        return 1;
    }

    volume = cylinder_volume(radius, height);

    if (volume < 0.0) {
        printf("Error: Radius and height must be positive values.\n");
        return 1;
    }

    printf("Volume of cylinder: %.2f\n", volume);

    return 0;
}