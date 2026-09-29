#include <stdio.h>
#include <stdlib.h>

int count_odd_elements(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int expected_size = 5;
    int *my_list = (int *)malloc(expected_size * sizeof(int));
    
    if (my_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    my_list[0] = 1;
    my_list[1] = 4;
    my_list[2] = 7;
    my_list[3] = 8;
    my_list[4] = 11;

    int odd_count = count_odd_elements(my_list, expected_size);

    printf("Number of odd elements: %d\n", odd_count);

    free(my_list);
    my_list = NULL;

    return 0;
}