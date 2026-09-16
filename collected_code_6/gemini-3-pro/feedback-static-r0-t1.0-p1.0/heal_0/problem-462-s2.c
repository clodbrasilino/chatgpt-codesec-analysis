#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}

void find_combinations(int *arr, int n) {
    if (n < 0 || arr == NULL) {
        return;
    }
    
    int total_combinations = 1 << n;
    
    for (int i = 0; i < total_combinations; i++) {
        int *temp = (int *)malloc(n * sizeof(int));
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        int temp_size = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                temp[temp_size++] = arr[j];
            }
        }
        
        print_array(temp, temp_size);
        free(temp);
    }
}

int main(void) {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    find_combinations(arr, n);
    
    return EXIT_SUCCESS;
}