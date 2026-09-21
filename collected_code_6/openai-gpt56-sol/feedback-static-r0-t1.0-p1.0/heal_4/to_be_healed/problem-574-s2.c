#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
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

static int discard_line(int ch)
{
    while (ch != '\n' && ch != EOF) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == MAX_INPUT_LENGTH) {
            int status = discard_line(ch);
            free(buffer);
            /* Possible weaknesses found:
             *  Same value in both branches of ternary operator. [duplicateValueTernary]
             */
            return status == 0 ? -1 : -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity >= MAX_INPUT_LENGTH + 1U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity <= (MAX_INPUT_LENGTH + 1U) / 2U
                               ? capacity * 2U
                               : MAX_INPUT_LENGTH + 1U;

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

static int parse_double(const char **cursor, double *value)
{
    char *end;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    errno = 0;
    *value = strtod(*cursor, &end);

    if (end == *cursor || errno == ERANGE || !isfinite(*value)) {
        return -1;
    }

    *cursor = end;
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

    while (isspace((unsigned char)*cursor)) {
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