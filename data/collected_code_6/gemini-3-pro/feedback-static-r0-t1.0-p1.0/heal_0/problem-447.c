#include <stdio.h>
#include <stdlib.h>

void cube_elements(int* array, size_t length) {
    if (array == NULL) {
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        array[i] = array[i] * array[i] * array[i];
    }
}

int main(void) {
    size_t length = 5;
    int* my_list = (int*)malloc(length * sizeof(int));
    if (my_list == NULL) {
        return EXIT_FAILURE;
    }

    my_list[0] = 1;
    my_list[1] = 2;
    my_list[2] = 3;
    my_list[3] = 4;
    my_list[4] = 5;

    cube_elements(my_list, length);

    for (size_t i = 0; i < length; ++i) {
        printf("%d ", my_list[i]);
    }
    printf("\n");

    free(my_list);
    my_list = NULL;

    return EXIT_SUCCESS;
}