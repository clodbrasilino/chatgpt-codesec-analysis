#include <stdio.h>

double calculate_average_of_cubes(int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    double n_dbl = (double)n;
    return (n_dbl * (n_dbl + 1.0) * (n_dbl + 1.0)) / 4.0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=10', assigned value is 10
     */
    int n = 10;
    
    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     */
    if (n <= 0) {
        fprintf(stderr, "Invalid input: n must be a positive integer.\n");
        return 1;
    }
    
    double average = calculate_average_of_cubes(n);
    printf("%f\n", average);
    
    return 0;
}