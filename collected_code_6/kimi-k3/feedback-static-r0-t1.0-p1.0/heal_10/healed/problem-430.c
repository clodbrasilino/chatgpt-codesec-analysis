#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

#define PARABOLA_SUCCESS 0
#define PARABOLA_ERROR_INVALID_INPUT -1
#define PARABOLA_ERROR_VERTICAL -2
#define BUFFER_SIZE 256

typedef struct {
    double h;
    double k;
    double p;
    int is_vertical;
} Parabola;

typedef struct {
    double value;
    int is_vertical_line;
} Directrix;

int calculate_directrix(const Parabola *parabola, Directrix *directrix) {
    if (parabola == NULL || directrix == NULL) {
        return PARABOLA_ERROR_INVALID_INPUT;
    }
    
    if (fabs(parabola->p) < 1e-12) {
        return PARABOLA_ERROR_INVALID_INPUT;
    }
    
    if (parabola->is_vertical) {
        directrix->value = parabola->k - parabola->p;
        directrix->is_vertical_line = 0;
    } else {
        directrix->value = parabola->h - parabola->p;
        directrix->is_vertical_line = 1;
    }
    
    return PARABOLA_SUCCESS;
}

int parse_double(const char *str, double *result) {
    char *endptr;
    double value;
    
    if (str == NULL || result == NULL) {
        return -1;
    }
    
    errno = 0;
    value = strtod(str, &endptr);
    
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return -1;
    }
    
    *result = value;
    return 0;
}

int read_line(char *buffer, size_t size) {
    size_t len;
    int c;
    int overflow = 0;
    
    if (buffer == NULL || size == 0 || size > INT_MAX) {
        return -1;
    }
    
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }
    
    len = strnlen(buffer, size);
    
    if (len == 0) {
        return -1;
    }
    
    if (len < size && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1 && buffer[len - 1] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF) {
            overflow = 1;
        }
        if (overflow) {
            return -1;
        }
    }
    
    return 0;
}

int main(void) {
    Parabola parabola;
    Directrix directrix;
    char buffer[BUFFER_SIZE];
    int result;
    int orientation;
    
    printf("Parabola Directrix Calculator\n");
    printf("Enter 1 for vertical parabola (y-k)^2 = 4p(x-h)\n");
    printf("Enter 0 for horizontal parabola (x-h)^2 = 4p(y-k)\n");
    printf("Orientation: ");
    
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(buffer, "%d", &orientation) != 1) {
        fprintf(stderr, "Invalid orientation input\n");
        return EXIT_FAILURE;
    }
    
    if (orientation != 0 && orientation != 1) {
        fprintf(stderr, "Orientation must be 0 or 1\n");
        return EXIT_FAILURE;
    }
    
    parabola.is_vertical = orientation;
    
    printf("Enter h (x-coordinate of vertex): ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_double(buffer, &parabola.h) != 0) {
        fprintf(stderr, "Invalid numeric input for h\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter k (y-coordinate of vertex): ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_double(buffer, &parabola.k) != 0) {
        fprintf(stderr, "Invalid numeric input for k\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter p (distance from vertex to focus, non-zero): ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (parse_double(buffer, &parabola.p) != 0) {
        fprintf(stderr, "Invalid numeric input for p\n");
        return EXIT_FAILURE;
    }
    
    result = calculate_directrix(&parabola, &directrix);
    
    if (result != PARABOLA_SUCCESS) {
        fprintf(stderr, "Error calculating directrix: invalid parameters\n");
        return EXIT_FAILURE;
    }
    
    if (directrix.is_vertical_line) {
        printf("Directrix: x = %.6f\n", directrix.value);
    } else {
        printf("Directrix: y = %.6f\n", directrix.value);
    }
    
    return EXIT_SUCCESS;
}