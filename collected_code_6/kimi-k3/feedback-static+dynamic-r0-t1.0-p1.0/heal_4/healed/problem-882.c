#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

double calculate_perimeter(double base, double side) {
    if (base < 0.0 || side < 0.0 || !isfinite(base) || !isfinite(side)) {
        return -1.0;
    }
    if (base > DBL_MAX / 2.0 || side > DBL_MAX / 2.0) {
        return -1.0;
    }
    return 2.0 * (base + side);
}

int read_input(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return -1;
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }
    
    buffer[size - 1] = '\0';
    
    size_t len = strnlen(buffer, size);
    if (len == 0) {
        return -1;
    }
    
    if (buffer[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -2;
    }
    
    buffer[len - 1] = '\0';
    
    return 0;
}

int parse_double(const char *buffer, double *value) {
    if (buffer == NULL || value == NULL) {
        return -1;
    }
    
    char *endptr;
    errno = 0;
    double result = strtod(buffer, &endptr);
    
    if (endptr == buffer || errno == ERANGE || !isfinite(result)) {
        return -1;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return -1;
    }
    
    *value = result;
    return 0;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    double base, side;
    
    printf("Enter base: ");
    int status = read_input(buffer, sizeof(buffer));
    if (status == -1) {
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (parse_double(buffer, &base) != 0) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter side: ");
    status = read_input(buffer, sizeof(buffer));
    if (status == -1) {
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (parse_double(buffer, &side) != 0) {
        fprintf(stderr, "Invalid input for side\n");
        return EXIT_FAILURE;
    }
    
    double perimeter = calculate_perimeter(base, side);
    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid dimensions or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter: %f\n", perimeter);
    return EXIT_SUCCESS;
}