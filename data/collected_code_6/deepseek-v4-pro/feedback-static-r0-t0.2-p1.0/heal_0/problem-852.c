#include <stdio.h>
#include <stdlib.h>

int remove_negatives(int *list, int size) {
    if (list == NULL || size <= 0) {
        return 0;
    }
    
    int write_index = 0;
    
    for (int read_index = 0; read_index < size; read_index++) {
        if (list[read_index] >= 0) {
            list[write_index] = list[read_index];
            write_index++;
        }
    }
    
    return write_index;
}

int main(void) {
    int test_list[] = {5, -3, 8, -1, 0, 7, -6, 4};
    int original_size = sizeof(test_list) / sizeof(test_list[0]);
    
    printf("Original list: ");
    for (int i = 0; i < original_size; i++) {
        printf("%d ", test_list[i]);
    }
    printf("\n");
    
    int new_size = remove_negatives(test_list, original_size);
    
    printf("List after removing negatives: ");
    for (int i = 0; i < new_size; i++) {
        printf("%d ", test_list[i]);
    }
    printf("\n");
    
    printf("New size: %d\n", new_size);
    
    return 0;
}