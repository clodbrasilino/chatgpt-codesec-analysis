#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <limits.h>

static double calculate_perimeter(int sides, double side_length)
{
    return sides * side_length;
}

static int read_line(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }
    
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) { }
    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *endptr;
    long sides;
    double side_length;
    double perimeter;
    int status;

    status = read_line(input_buffer, sizeof(input_buffer));
    if (status == 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (status == -1) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    sides = strtol(input_buffer, &endptr, 10);
    if (errno != 0 || endptr == input_buffer || *endptr != '\0' || sides < 3 || sides > 1000) {
        fprintf(stderr, "Invalid number of sides\n");
        return EXIT_FAILURE;
    }

    status = read_line(input_buffer, sizeof(input_buffer));
    if (status == 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (status == -1) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side_length = strtod(input_buffer, &endptr);
    if (errno != 0 || endptr == input_buffer || *endptr != '\0' || side_length <= 0.0 || !isfinite(side_length)) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_perimeter((int)sides, side_length);
    
    if (!isfinite(perimeter)) {
        fprintf(stderr, "Calculation overflow\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", perimeter);
    return EXIT_SUCCESS;
}