#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

int rotate_array(int *arr, size_t size, size_t split_pos)
{
    int *temp;
    size_t first_part_size;
    size_t second_part_size;
    
    if (arr == NULL || size == 0) {
        return -1;
    }
    
    if (split_pos >= size) {
        return -1;
    }
    
    if (size > SIZE_MAX / sizeof(int)) {
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
    
    temp = malloc(first_part_size * sizeof(int));
    
    if (temp == NULL) {
        return -1;
    }
    
    if (first_part_size > 0) {
        if (first_part_size > SIZE_MAX / sizeof(int)) {
            free(temp);
            return -1;
        }
        if (memcpy(temp, arr, first_part_size * sizeof(int)) != temp) {
            free(temp);
            return -1;
        }
    }
    
    if (second_part_size > 0) {
        if (second_part_size > SIZE_MAX / sizeof(int)) {
            free(temp);
            return -1;
        }
        if (memmove(arr, arr + first_part_size, second_part_size * sizeof(int)) != arr) {
            free(temp);
            return -1;
        }
    }
    
    if (first_part_size > 0) {
        if (first_part_size > SIZE_MAX / sizeof(int)) {
            free(temp);
            return -1;
        }
        if (memcpy(arr + second_part_size, temp, first_part_size * sizeof(int)) != (arr + second_part_size)) {
            free(temp);
            return -1;
        }
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