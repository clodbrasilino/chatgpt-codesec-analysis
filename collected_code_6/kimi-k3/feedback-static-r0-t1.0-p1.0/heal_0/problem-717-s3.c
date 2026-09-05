#include <stdio.h>
#include <math.h>

double calculateStandardDeviation(double data[], int size) {
    if (size <= 0) {
        return -1.0;
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    double mean = sum / size;
    double variance = 0.0;

    for (int i = 0; i < size; i++) {
        variance += pow(data[i] - mean, 2);
    }

    variance /= size;

    return sqrt(variance);
}

int main() {
    double data[] = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    int size = sizeof(data) / sizeof(data[0]);

    double stdDev = calculateStandardDeviation(data, size);
    if (stdDev >= 0) {
        printf("Standard Deviation: %.6f\n", stdDev);
    } else {
        printf("Invalid data size.\n");
    }

    return 0;
}