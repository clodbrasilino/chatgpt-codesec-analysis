#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

bool check_element_exists(const Tuple *tuple, int element) {
    if (tuple == NULL || tuple->data == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->data[i] == element) {
            return true;
        }
    }

    return false;
}

int main(void) {
    size_t size = 5;
    int *data = (int *)malloc(size * sizeof(int));
    
    if (data == NULL) {
        return EXIT_FAILURE;
    }

    data[0] = 10;
    data[1] = 20;
    data[2] = 30;
    data[3] = 40;
    data[4] = 50;

    Tuple my_tuple = {data, size};

    bool exists = check_element_exists(&my_tuple, 30);
    if (exists) {
        printf("Element exists\n");
    } else {
        printf("Element does not exist\n");
    }

    free(data);
    my_tuple.data = NULL;

    return EXIT_SUCCESS;
}