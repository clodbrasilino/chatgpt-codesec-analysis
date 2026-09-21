#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

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

static int discard_remaining_input(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strchr'
         */
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)(MAX_INPUT_LENGTH + 2U), stdin) == NULL) {
        free(buffer);
        return ferror(stdin) ? -1 : 0;
    }

    /* Possible weaknesses found:
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     */
    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        int status = discard_remaining_input();
        free(buffer);
        return status < 0 ? -2 : -1;
    } else if (!feof(stdin)) {
        int status = discard_remaining_input();
        free(buffer);
        return status < 0 ? -2 : -1;
    }

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
    while (isspace((unsigned char)*start)) {
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