#include <stdio.h>
#include <float.h>

double maxCuboidVolume(double sum) {
    if (sum <= 0.0) {
        return -1.0;
    }
    double side = sum / 3.0;
    return side * side * side;
}

int main(void) {
    double sum;
    int result;

    printf("Enter the sum of sides: ");
    result = scanf("%lf", &sum);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    double volume = maxCuboidVolume(sum);

    if (volume < 0.0) {
        fprintf(stderr, "Sum of sides must be positive\n");
        return 1;
    }

    printf("Maximum volume: %.6f\n", volume);
    return 0;
}