#include <stdio.h>
#include <stdlib.h>

size_t count_integers(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        count++;
    }
    
    return count;
}

int main(void) {
    size_t size = 5;
    int *my_list = (int *)malloc(size * sizeof(int));
    
    if (my_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    my_list[0] = 10;
    my_list[1] = 20;
    my_list[2] = 30;
    my_list[3] = 40;
    my_list[4] = 50;
    
    size_t result = count_integers(my_list, size);
    printf("First count: %zu\n", result);
    
    free(my_list);
    my_list = NULL;
    
    size_t null_result = count_integers(NULL, 0);
    printf("Null list count: %zu\n", null_result);
    
    return EXIT_SUCCESS;
}