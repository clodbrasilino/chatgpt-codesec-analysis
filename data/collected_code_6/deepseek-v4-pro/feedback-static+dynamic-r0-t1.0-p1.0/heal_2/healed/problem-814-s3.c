#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

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
    char input[256];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (!is_valid_number(input, &d1) || d1 <= 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (!is_valid_number(input, &d2) || d2 <= 0) {
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    printf("%.2f\n", area);

    return EXIT_SUCCESS;
}