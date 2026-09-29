#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double radius, double height, double *area)
{
    double result;
    const double pi = acos(-1.0);

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0 || !isfinite(pi)) {
        return 0;
    }

    result = 2.0 * pi * radius * height;
    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n';
}

static int read_double(const char *prompt, double *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double result;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    capacity = 64;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *temporary;

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > 4096 / 2) {
                discard_line();
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                discard_line();
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (length == 0 || ferror(stdin))) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    result = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(result)) {
        free(buffer);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = result;
    free(buffer);
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (!read_double("Enter the radius: ", &radius) ||
        !read_double("Enter the height: ", &height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(radius, height, &area)) {
        fputs("Unable to calculate the lateral surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}