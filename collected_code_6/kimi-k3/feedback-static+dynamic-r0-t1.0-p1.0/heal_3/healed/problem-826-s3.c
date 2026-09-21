#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#define INPUT_BUFFER_SIZE 256

typedef enum {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} TriangleType;

static int parse_positive_double(const char *str, double *out)
{
    char *endptr = NULL;
    double value;
    
    if (str == NULL || out == NULL) {
        return 0;
    }
    
    errno = 0;
    value = strtod(str, &endptr);
    
    if (endptr == str) {
        return 0;
    }
    
    if (errno == ERANGE) {
        return 0;
    }
    
    if (value <= 0.0 || !isfinite(value)) {
        return 0;
    }
    
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    
    if (*endptr != '\0' && *endptr != '\n') {
        return 0;
    }
    
    *out = value;
    return 1;
}

static TriangleType classify_triangle(double a, double b, double c)
{
    double sum_ab;
    double sum_ac;
    double sum_bc;
    
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return TRIANGLE_INVALID;
    }
    
    sum_ab = a + b;
    sum_ac = a + c;
    sum_bc = b + c;
    
    if (!isfinite(sum_ab) || !isfinite(sum_ac) || !isfinite(sum_bc)) {
        return TRIANGLE_INVALID;
    }
    
    if (sum_ab <= c || sum_ac <= b || sum_bc <= a) {
        return TRIANGLE_INVALID;
    }
    
    if (a == b && b == c) {
        return TRIANGLE_EQUILATERAL;
    }
    
    if (a == b || b == c || a == c) {
        return TRIANGLE_ISOSCELES;
    }
    
    return TRIANGLE_SCALENE;
}

static const char *triangle_type_string(TriangleType type)
{
    switch (type) {
        case TRIANGLE_EQUILATERAL:
            return "Equilateral";
        case TRIANGLE_ISOSCELES:
            return "Isosceles";
        case TRIANGLE_SCALENE:
            return "Scalene";
        case TRIANGLE_INVALID:
        default:
            return "Invalid";
    }
}

static int read_line(char *buffer, size_t size)
{
    size_t len;
    
    if (buffer == NULL || size == 0) {
        return 0;
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }
    
    len = strnlen(buffer, size);
    
    if (len == size - 1 && buffer[len - 1] != '\n') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }
    
    return 1;
}

int main(void)
{
    char input_buffer[INPUT_BUFFER_SIZE];
    double side_a = 0.0;
    double side_b = 0.0;
    double side_c = 0.0;
    TriangleType result;
    int read_result;
    
    printf("Enter three sides of triangle (space-separated): ");
    
    read_result = read_line(input_buffer, sizeof(input_buffer));
    
    if (read_result == 0) {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }
    
    if (read_result == -1) {
        fprintf(stderr, "Error: Input too long\n");
        return EXIT_FAILURE;
    }
    
    {
        char *token;
        char *saveptr = NULL;
        int token_count = 0;
        double sides[3] = {0.0, 0.0, 0.0};
        
        token = strtok_r(input_buffer, " \t\n", &saveptr);
        
        while (token != NULL && token_count < 3) {
            if (!parse_positive_double(token, &sides[token_count])) {
                fprintf(stderr, "Error: Invalid number format\n");
                return EXIT_FAILURE;
            }
            token_count++;
            token = strtok_r(NULL, " \t\n", &saveptr);
        }
        
        if (token_count != 3) {
            fprintf(stderr, "Error: Expected 3 sides, got %d\n", token_count);
            return EXIT_FAILURE;
        }
        
        if (token != NULL) {
            fprintf(stderr, "Error: Too many arguments\n");
            return EXIT_FAILURE;
        }
        
        side_a = sides[0];
        side_b = sides[1];
        side_c = sides[2];
    }
    
    result = classify_triangle(side_a, side_b, side_c);
    
    printf("Triangle type: %s\n", triangle_type_string(result));
    
    if (result == TRIANGLE_INVALID) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}