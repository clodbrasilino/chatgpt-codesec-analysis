#include <stdio.h>
#include <stdlib.h>

double* divideLists(double* list1, double* list2, int size) {
    double* result = (double*)malloc(size * sizeof(double));
    if(result == NULL) {
        return NULL;
    }
    
    for(int i = 0; i < size; i++) {
        if(list2[i] != 0) {
            result[i] = list1[i] / list2[i];
        } else {
            result[i] = 0;
        }
    }
    return result;
}

int main() {
    int size = 5;
    double list1[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    double list2[] = {2.0, 4.0, 5.0, 8.0, 10.0};
    double* result = divideLists(list1, list2, size);
    
    if(result == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for(int i = 0; i < size; i++) {
        printf("%f ", result[i]);
    }
    
    free(result);
    return 0;
}