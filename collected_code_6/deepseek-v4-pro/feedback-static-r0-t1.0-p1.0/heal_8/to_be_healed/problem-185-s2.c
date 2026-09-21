#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

Point find_focus(Parabola p) {
    Point focus;
    double h = -p.b / (2 * p.a);
    double k = p.a * h * h + p.b * h + p.c;
    double p_val = 1.0 / (4 * p.a);
    
    focus.x = h;
    focus.y = k + p_val;
    
    return focus;
}

int main(void) {
    Parabola p;
    Point focus;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t input_length;
    int valid_input;
    char *newline_pos;
    
    printf("Enter coefficients a, b, c for parabola y = ax^2 + bx + c:\n");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    input_length = strnlen(input, sizeof(input));
    
    if (input_length >= sizeof(input) - 1 && input[sizeof(input) - 1] != '\0') {
        input[sizeof(input) - 1] = '\0';
        input_length = sizeof(input) - 1;
    }
    
    newline_pos = memchr(input, '\n', input_length);
    if (newline_pos != NULL) {
        *newline_pos = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stdin);
        }
    }
    
    valid_input = 1;
    if (sscanf(input, "%lf %lf %lf", &p.a, &p.b, &p.c) != 3) {
        valid_input = 0;
    }
    
    if (!valid_input) {
        fprintf(stderr, "Invalid input. Please enter three numbers.\n");
        return EXIT_FAILURE;
    }
    
    if (fabs(p.a) < 1e-10) {
        fprintf(stderr, "Error: Coefficient 'a' cannot be zero.\n");
        return EXIT_FAILURE;
    }
    
    focus = find_focus(p);
    
    printf("Focus: (%.6f, %.6f)\n", focus.x, focus.y);
    
    return EXIT_SUCCESS;
}