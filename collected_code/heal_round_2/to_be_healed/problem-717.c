#include <math.h>
#include <stdlib.h>
#include <assert.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

double calculateStandardDeviation(const int arr[], const int size) {
    assert(arr != NULL && size > 0);
    
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

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    double stdDev = calculateStandardDeviation(arr, size);
    
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("The standard deviation is %.2f\n", stdDev);
    
    return 0;
}