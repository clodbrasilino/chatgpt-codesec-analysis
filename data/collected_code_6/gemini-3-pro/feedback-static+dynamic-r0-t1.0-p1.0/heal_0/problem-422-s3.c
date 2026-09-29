#include <stdio.h>
#include <stdlib.h>

double average_of_cubes(unsigned int n) {
    if (n == 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (unsigned int i = 1; i <= n; i++) {
        sum += (double)i * (double)i * (double)i;
    }
    
    return sum / n;
}

int main(void) {
    unsigned int n;
    int result;

    result = scanf("%u", &n);
    if (result != 1) {
        return EXIT_FAILURE;
    }

    double average = average_of_cubes(n);
    printf("%f\n", average);

    return EXIT_SUCCESS;
}