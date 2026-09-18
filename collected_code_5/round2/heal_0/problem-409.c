#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_prod_from_pairs(int* tuple_arr, int tuple_num){
    if(tuple_num < 2 || tuple_num % 2 != 0)
        return -1;
    
    int min_prod = INT_MAX;
    for(int i = 0; i < tuple_num; i += 2){
        int temp_prod = tuple_arr[i] * tuple_arr[i+1];
        if(temp_prod < min_prod) 
            min_prod = temp_prod;
    }
    
    return min_prod;
}

int main() {
    int arr_size = 8;
    int* arr = malloc(arr_size * sizeof(int));
    if (arr == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    for (int i = 0; i < arr_size; ++i) {
        arr[i] = i + 1;
    }

    int result = min_prod_from_pairs(arr, arr_size);
    if (result == -1) {
        printf("Invalid input array\n");
    } else {
        printf("Minimum product from pairs is: %d\n", result);
    }

    free(arr);
    return 0;
}