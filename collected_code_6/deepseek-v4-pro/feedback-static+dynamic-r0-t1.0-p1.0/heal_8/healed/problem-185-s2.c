#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256
#define EXPECTED_PARTS 3

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
    char input[INPUT_BUFFER_SIZE];
    size_t len;
    int items_read;
    
    printf("Enter coefficients a, b, c for parabola y = ax^2 + bx + c:\n");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    len = strlen(input);
    
    if (len == 0 || input[0] == '\n') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] != '\n' && len == sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    items_read = sscanf(input, "%lf %lf %lf", &p.a, &p.b, &p.c);
    if (items_read != EXPECTED_PARTS) {
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