#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_duplicate_frequency(int *arr, int size, int **freq_arr, int **values_arr) {
    if (arr == NULL || freq_arr == NULL || values_arr == NULL || size <= 0) {
        return -1;
    }
    
    int *freq = (int *)malloc(size * sizeof(int));
    int *values = (int *)malloc(size * sizeof(int));
    
    if (freq == NULL || values == NULL) {
        free(freq);
        free(values);
        return -1;
    }
    
    int count = 0;
    int i = 0;
    
    while (i < size) {
        int j = i;
        while (j < size && arr[j] == arr[i]) {
            j++;
        }
        
        if (j - i > 1) {
            values[count] = arr[i];
            freq[count] = j - i;
            count++;
        }
        
        i = j;
    }
    
    if (count == 0) {
        free(freq);
        free(values);
        *freq_arr = NULL;
        *values_arr = NULL;
        return 0;
    }
    
    int *resized_freq = (int *)realloc(freq, count * sizeof(int));
    int *resized_values = (int *)realloc(values, count * sizeof(int));
    
    if (resized_freq == NULL || resized_values == NULL) {
        free(freq);
        free(values);
        return -1;
    }
    
    *freq_arr = resized_freq;
    *values_arr = resized_values;
    
    return count;
}

int main(void) {
    int arr[] = {1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 5, 6, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int *freq = NULL;
    int *values = NULL;
    
    int count = count_duplicate_frequency(arr, size, &freq, &values);
    
    if (count < 0) {
        printf("Error processing array\n");
        return 1;
    }
    
    if (count == 0) {
        printf("No consecutive duplicates found\n");
        return 0;
    }
    
    printf("Consecutive duplicates:\n");
    for (int i = 0; i < count; i++) {
        printf("Value %d: %d times\n", values[i], freq[i]);
    }
    
    free(freq);
    free(values);
    
    return 0;
}