#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int id;
    int value;
};

void replace_duplicates(struct Tuple* array, size_t size, int custom_value) {
    if (array == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        int current_value = array[i].value;
        int is_duplicate = 0;

        for (size_t j = i + 1; j < size; j++) {
            if (array[j].value == current_value) {
                array[j].value = custom_value;
                is_duplicate = 1;
            }
        }
        
        if (is_duplicate && array[i].value != custom_value) {
            array[i].value = custom_value;
        }
    }
}

int main(void) {
    size_t size = 6;
    struct Tuple* array = (struct Tuple*)malloc(size * sizeof(struct Tuple));
    if (array == NULL) {
        return 1;
    }

    array[0].id = 1; array[0].value = 10;
    array[1].id = 2; array[1].value = 20;
    array[2].id = 3; array[2].value = 10;
    array[3].id = 4; array[3].value = 30;
    array[4].id = 5; array[4].value = 20;
    array[5].id = 6; array[5].value = 40;

    int custom_value = -1;

    replace_duplicates(array, size, custom_value);

    for (size_t i = 0; i < size; i++) {
        printf("id: %d, value: %d\n", array[i].id, array[i].value);
    }

    free(array);
    array = NULL;

    return 0;
}