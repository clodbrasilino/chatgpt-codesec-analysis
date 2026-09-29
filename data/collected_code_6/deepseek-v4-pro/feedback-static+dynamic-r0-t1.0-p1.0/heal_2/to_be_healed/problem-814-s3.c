#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 25, got <no output>
  *  test case 2 failed: expected 4, got <no output>
  *  test case 0 failed: expected 100, got <no output>
  */

double rhombus_area(double diagonal1, double diagonal2) {
    return (diagonal1 * diagonal2) / 2.0;
}

int is_valid_number(const char *str, double *result) {
    char *endptr;
    errno = 0;
    *result = strtod(str, &endptr);
    
    if (errno == ERANGE) {
        return 0;
    }
    
    if (endptr == str) {
        return 0;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return 0;
        }
        endptr++;
    }
    
    return 1;
}

int main(void) {
    double d1, d2, area;
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("Enter first diagonal: ");
    nread = getline(&input, &len, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
    }
    
    if (!is_valid_number(input, &d1) || d1 <= 0) {
        fprintf(stderr, "Invalid input for first diagonal\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Enter second diagonal: ");
    nread = getline(&input, &len, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
    }
    
    if (!is_valid_number(input, &d2) || d2 <= 0) {
        fprintf(stderr, "Invalid input for second diagonal\n");
        free(input);
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    printf("Area of rhombus: %.2f\n", area);

    free(input);
    return EXIT_SUCCESS;
}