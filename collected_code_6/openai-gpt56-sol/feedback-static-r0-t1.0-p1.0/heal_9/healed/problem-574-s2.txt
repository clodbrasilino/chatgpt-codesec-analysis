#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4096U

static int cylinder_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);
    double result;

    if (area == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    result = 2.0 * pi * radius * (radius + height);
    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int discard_remainder_of_line(void)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t length = 0U;

        while (length < sizeof buffer && buffer[length] != '\0') {
            if (buffer[length] == '\n') {
                return 0;
            }
            ++length;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    size_t length = 0U;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return ferror(stdin) ? -1 : 0;
    }

    while (length < capacity && buffer[length] != '\0') {
        ++length;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        *line = buffer;
        return 1;
    }

    if (length > (size_t)MAX_INPUT_LENGTH) {
        free(buffer);
        return discard_remainder_of_line() == 0 ? -2 : -1;
    }

    if (feof(stdin)) {
        *line = buffer;
        return 1;
    }

    free(buffer);
    return discard_remainder_of_line() == 0 ? -2 : -1;
}

static int parse_double(const char **cursor, double *value)
{
    const char *start;
    char *end;
    double parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return -1;
    }

    start = *cursor;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(parsed)) {
        return -1;
    }

    *cursor = end;
    *value = parsed;
    return 0;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    double radius;
    double height;
    double area;
    int status;

    if (printf("Enter radius and height: ") < 0 || fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write prompt.\n");
        return EXIT_FAILURE;
    }

    status = read_line(&input);

    if (status == -2) {
        fprintf(stderr, "Input exceeds the maximum length.\n");
        return EXIT_FAILURE;
    }

    if (status < 0) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (status == 0) {
        fprintf(stderr, "No input received.\n");
        return EXIT_FAILURE;
    }

    cursor = input;

    if (parse_double(&cursor, &radius) != 0) {
        fprintf(stderr, "Invalid radius.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (parse_double(&cursor, &height) != 0) {
        fprintf(stderr, "Invalid height.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fprintf(stderr, "Unexpected input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (cylinder_surface_area(radius, height, &area) != 0) {
        fprintf(stderr, "Unable to calculate surface area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}