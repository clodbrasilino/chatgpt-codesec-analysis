#include <stdio.h>
#include <math.h>

double findMaxPeriodicValue(double (*function)(double), double period, double start, double end) {
    double maxVal = function(start);
    double interval = (end - start) / period;
    
    for (int i = 1; i < period; i++) {
        double x = start + interval * i;
        double y = function(x);
        
        if (y > maxVal) {
            maxVal = y;
        }
    }
    
    return maxVal;
}

// Example usage
double sineFunction(double x) {
    return sin(x);
}

int main() {
    double period = 2 * M_PI;  // Period of the function (e.g., 2π for sine/cosine)
    double start = 0.0;       // Start point
    double end = 2 * M_PI;    // End point
    
    double maxVal = findMaxPeriodicValue(sineFunction, period, start, end);
    
    printf("Maximum value: %f\n", maxVal);
    
    return 0;
}