#include <stdio.h>
#include <stdlib.h>

int count_integers(int *list, size_t size) {
    int count = 0;
    
    for (size_t i = 0; i < size; i++) {
        count++;
    }
    
    return count;
}

int main(void) {
    int test_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t list_size = sizeof(test_list) / sizeof(test_list[0]);
    
    int result = count_integers(test_list, list_size);
    printf("Number of integers: %d\n", result);
    
    int *empty_list = NULL;
    result = count_integers(empty_list, 0);
    printf("Number of integers in empty list: %d\n", result);
    
    return 0;
}