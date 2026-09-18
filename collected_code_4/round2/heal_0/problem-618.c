#include <stdio.h>
#include <stdlib.h>

double* divideTwoLists(double* list1, double* list2, int length_list1, int length_list2) {
    
    if(length_list1 != length_list2 || list1 == NULL || list2 == NULL) {
        printf("Invalid input.\n");
        exit(0);
    }
    
    double* result = (double*)malloc(length_list1 * sizeof(double));
    if(result == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    
    for(int i = 0; i < length_list1; i++) {
        if(list2[i] == 0) {
            printf("Division by zero occurred.\n");
            free(result);
            exit(0);
        }
        result[i] = list1[i] / list2[i];
    }
    
    return result;
}

int main() {
    
    int length = 3;

    double list1[] = {1.0, 2.0, 3.0};
    double list2[] = {4.0, 5.0, 6.0};
    
    double* result = divideTwoLists(list1, list2, length, length);
    
    printf("Result:\n");
    for(int i = 0; i < length; i++) {
        printf("%f\n", result[i]);
    }

    free(result);

    return 0;
}