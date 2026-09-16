#include <stdio.h>
#include <stdlib.h>

int calculate_directrix(double a, double b, double c, double *directrix);

int calculate_directrix(double a, double b, double c, double *directrix) {
    if (a == 0.0 || directrix == NULL) {
        return -1;
    }

    *directrix = c - ((b * b + 1.0) / (4.0 * a));
    
    return 0;
}

int main(void) {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double directrix = 0.0;
    int read_status = 0;

    read_status = scanf("%lf %lf %lf", &a, &b, &c);
    
    if (read_status != 3) {
        fprintf(stderr, "Invalid input formatting\n");
        return EXIT_FAILURE;
    }

    if (calculate_directrix(a, b, c, &directrix) != 0) {
        fprintf(stderr, "Invalid parameters: 'a' cannot be zero\n");
        return EXIT_FAILURE;
    }

    printf("%.4f\n", directrix);

    return EXIT_SUCCESS;
}