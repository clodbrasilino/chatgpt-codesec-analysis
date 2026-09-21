#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

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
    size_t len;
    
    printf("Enter coefficients a, b, c for parabola y = ax^2 + bx + c:\n");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(input, "%lf %lf %lf", &p.a, &p.b, &p.c) != 3) {
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