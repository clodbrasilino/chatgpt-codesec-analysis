#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

/* Possible weaknesses found:
 *  Parameter 'sides' can be declared as const array [constParameter]
 */
double calculate_perimeter(double sides[5]) {
    double perimeter = 0.0;
    for (int i = 0; i < 5; i++) {
        perimeter += sides[i];
    }
    return perimeter;
}

int main(void) {
    double sides[5];
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;
    
    printf("Enter the lengths of the five sides of the pentagon: ");
    
    for (int i = 0; i < 5; i++) {
        result = scanf("%lf", &sides[i]);
        if (result != 1) {
            fprintf(stderr, "Error: Invalid input for side %d\n", i + 1);
            return EXIT_FAILURE;
        }
        if (sides[i] < 0.0) {
            fprintf(stderr, "Error: Side length cannot be negative\n");
            return EXIT_FAILURE;
        }
    }
    
    double perimeter = calculate_perimeter(sides);
    printf("Perimeter of the pentagon: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}