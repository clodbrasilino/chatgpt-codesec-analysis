#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <stddef.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 512

static double cylinder_volume(double radius, double height) {
    if (radius <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

static double safe_strtod(const char *str) {
    char *endptr;
    double val;

    if (str == NULL || *str == '\0') {
        return -1.0;
    }

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

static bool read_input_line(char *buffer, size_t buffer_size) {
    size_t len;

    if (buffer == NULL || buffer_size == 0) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    buffer[buffer_size - 1] = '\0';
    len = strnlen(buffer, buffer_size);
    if (len == 0) {
        return false;
    }

    if (len == buffer_size - 1 && buffer[buffer_size - 2] != '\n') {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
        return false;
    }

    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        return false;
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE + 1];
    double radius, height, volume;

    memset(input, 0, sizeof(input));

    printf("Enter radius: ");
    if (!read_input_line(input, INPUT_BUFFER_SIZE)) {
        printf("Error: Invalid input or input too long.\n");
        return 1;
    }

    radius = safe_strtod(input);
    if (radius < 0.0) {
        printf("Error: Invalid radius value.\n");
        return 1;
    }

    memset(input, 0, sizeof(input));

    printf("Enter height: ");
    if (!read_input_line(input, INPUT_BUFFER_SIZE)) {
        printf("Error: Invalid input or input too long.\n");
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