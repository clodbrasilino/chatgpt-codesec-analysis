#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int rotate_array(int *arr, size_t size, size_t split_pos)
{
    int *temp;
    size_t first_part_size;
    size_t second_part_size;
    size_t first_part_bytes;
    size_t second_part_bytes;
    
    if (arr == NULL || size == 0 || split_pos >= size) {
        return -1;
    }
    
    first_part_size = split_pos;
    second_part_size = size - first_part_size;
    
    if (first_part_size > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    if (second_part_size > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    
    first_part_bytes = first_part_size * sizeof(int);
    second_part_bytes = second_part_size * sizeof(int);
    
    temp = malloc(first_part_bytes);
    
    if (temp == NULL) {
        return -1;
    }
    
    if (first_part_bytes > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, arr, first_part_bytes);
    }
    
    if (second_part_bytes > 0) {
        memmove(arr, arr + first_part_size, second_part_bytes);
    }
    
    if (first_part_bytes > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr + second_part_size, temp, first_part_bytes);
    }
    
    free(temp);
    temp = NULL;
    
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t split_pos = 3;
    size_t i;
    
    printf("Original array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    if (rotate_array(arr, size, split_pos) != 0) {
        fprintf(stderr, "Error: Failed to rotate array\n");
        return EXIT_FAILURE;
    }
    
    printf("Rotated array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}