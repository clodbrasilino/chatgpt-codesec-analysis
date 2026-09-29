#include <stdio.h>

double find_average(int *tuple, int tupleSize) {
    double sum = 0;
    if (tuple == NULL || tupleSize <= 0) {
        return 0;
    }
    
    for(int i = 0; i < tupleSize; i++) {
         sum += tuple[i];
    }
    
    return sum / tupleSize;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int tupleSize = sizeof(tuple)/sizeof(tuple[0]);
    
    double average = find_average(tuple, tupleSize);
    printf("The average is: %.2f\n", average);

    return 0;
}