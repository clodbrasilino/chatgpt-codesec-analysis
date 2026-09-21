#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>

static double cylinder_volume(double radius, double height) {
    if (radius <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius * height;
}

static double safe_strtod(const char *str) {
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

static int read_input_line(char *buffer, size_t buffer_size) {
    size_t len;
    size_t pos;

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return 0;
    }

    len = 0;
    while (len < buffer_size && buffer[len] != '\0') {
        len++;
    }

    if (len >= buffer_size) {
        return 0;
    }

    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        return 0;
    }

    pos = 0;
    while (pos < len) {
        pos++;
    }

    return 1;
}

int main(void) {
    char input[512];
    double radius, height, volume;
    size_t input_len;

    printf("Enter radius: ");
    if (!read_input_line(input, sizeof(input))) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    input_len = 0;
    while (input_len < sizeof(input) && input[input_len] != '\0') {
        input_len++;
    }
    if (input_len >= sizeof(input)) {
        printf("Error: Input too long.\n");
        return 1;
    }

    radius = safe_strtod(input);
    if (radius < 0.0) {
        printf("Error: Invalid radius value.\n");
        return 1;
    }

    printf("Enter height: ");
    if (!read_input_line(input, sizeof(input))) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    input_len = 0;
    while (input_len < sizeof(input) && input[input_len] != '\0') {
        input_len++;
    }
    if (input_len >= sizeof(input)) {
        printf("Error: Input too long.\n");
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