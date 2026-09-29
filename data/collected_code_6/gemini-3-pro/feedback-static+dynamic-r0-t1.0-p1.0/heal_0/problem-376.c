#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

void replace_duplicate_tuples(Tuple* arr, size_t size, int custom_value) {
    if (arr == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        int is_duplicate = 0;
        for (size_t j = 0; j < i; j++) {
            if (arr[i].value == arr[j].value) {
                is_duplicate = 1;
                break;
            }
        }
        if (is_duplicate) {
            arr[i].value = custom_value;
        }
    }
}

int main(void) {
    size_t size = 5;
    Tuple* arr = (Tuple*)malloc(size * sizeof(Tuple));
    
    if (arr == NULL) {
        return 1;
    }

    arr[0].id = 1; arr[0].value = 10;
    arr[1].id = 2; arr[1].value = 20;
    arr[2].id = 3; arr[2].value = 10;
    arr[3].id = 4; arr[3].value = 30;
    arr[4].id = 5; arr[4].value = 20;

    int custom_value = -1;

    replace_duplicate_tuples(arr, size, custom_value);

    for (size_t i = 0; i < size; i++) {
        printf("Tuple %d: %d\n", arr[i].id, arr[i].value);
    }

    free(arr);
    return 0;
}