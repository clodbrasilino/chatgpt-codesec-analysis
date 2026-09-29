#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

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
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length >= MAX_INPUT_LENGTH) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            }
            free(buffer);
            return -1;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity >= MAX_INPUT_LENGTH + 1) {
                free(buffer);
                return -1;
            }

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            if (new_capacity > MAX_INPUT_LENGTH + 1) {
                new_capacity = MAX_INPUT_LENGTH + 1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    char *end;
    double radius;
    double height;
    double area;
    int read_status;

    printf("Enter radius and height: ");
    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write prompt.\n");
        return EXIT_FAILURE;
    }

    read_status = read_line(&input);
    if (read_status <= 0) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    radius = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE || !isfinite(radius)) {
        fprintf(stderr, "Invalid radius.\n");
        free(input);
        return EXIT_FAILURE;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    height = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE || !isfinite(height)) {
        fprintf(stderr, "Invalid height.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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