#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculate_parallelogram_perimeter(double base, double side) {
    if (base <= 0 || side <= 0) {
        return -1;
    }
    return 2 * (base + side);
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_double_input(const char *prompt, double *value) {
    char buffer[256];
    char *endptr;
    
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    *value = strtod(buffer, &endptr);
    
    if (endptr == buffer || *endptr != '\0') {
        return 0;
    }
    
    return 1;
}

int main(void) {
    double base = 0.0;
    double side = 0.0;
    double perimeter = 0.0;

    if (!read_double_input("Enter the base length of the parallelogram: ", &base)) {
        printf("Invalid input for base length.\n");
        return EXIT_FAILURE;
    }
    
    if (base <= 0) {
        printf("Invalid input for base length.\n");
        return EXIT_FAILURE;
    }

    if (!read_double_input("Enter the side length of the parallelogram: ", &side)) {
        printf("Invalid input for side length.\n");
        return EXIT_FAILURE;
    }
    
    if (side <= 0) {
        printf("Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_parallelogram_perimeter(base, side);
    if (perimeter < 0) {
        printf("Lengths must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    printf("The perimeter of the parallelogram is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}