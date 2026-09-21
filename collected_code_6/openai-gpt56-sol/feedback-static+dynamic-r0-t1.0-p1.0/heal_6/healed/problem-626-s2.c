#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    double result;

    if (area == NULL || !isfinite(radius) || radius <= 0.0) {
        return -1;
    }

    result = radius * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    for (length = 0U; length < size && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return 0;
        }
    }

    ch = fgetc(stdin);

    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 1;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double area;
    int read_result;

    read_result = read_line(input, sizeof input);

    if (read_result < 0) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    if (read_result > 0) {
        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || largest_inscribed_triangle(radius, &area) != 0) {
        fprintf(stderr, "Radius must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}