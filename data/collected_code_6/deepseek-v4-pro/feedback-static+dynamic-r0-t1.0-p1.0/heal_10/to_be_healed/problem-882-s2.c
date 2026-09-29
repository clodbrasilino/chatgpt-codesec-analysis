#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 400, got 60
  *  test case 2 failed: expected 144, got 34
  *  test case 1 failed: expected 600, got 70
  */

double calculate_parallelogram_perimeter(double base, double side) {
    if (base <= 0 || side <= 0) {
        return -1;
    }
    return 2 * (base + side);
}

void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_double_input(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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