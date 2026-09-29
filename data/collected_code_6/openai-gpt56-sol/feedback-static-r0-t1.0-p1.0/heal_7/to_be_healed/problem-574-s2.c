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

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0U;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(buffer);

            if (ferror(stdin)) {
                return -1;
            }

            return -2;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
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
    int read_status;

    if (printf("Enter radius and height: ") < 0 || fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write prompt.\n");
        return EXIT_FAILURE;
    }

    read_status = read_line(&input);

    if (read_status == -2) {
        fprintf(stderr, "Input exceeds the maximum length.\n");
        return EXIT_FAILURE;
    }

    if (read_status < 0) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
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