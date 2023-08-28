#include <math.h>

double calculateStandardDeviation(int arr[], int size) {
    double mean = 0.0, variance = 0.0;
    
    // Calculate mean
    for (int i = 0; i < size; i++) {
        mean += arr[i];
    }
    mean /= size;
    
    // Calculate variance
    for (int i = 0; i < size; i++) {
        variance += pow(arr[i] - mean, 2);
    }
    variance /= size;
    
    // Calculate standard deviation
    double standardDeviation = sqrt(variance);
    
    return standardDeviation;
}