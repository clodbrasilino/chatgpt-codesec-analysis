#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

size_t get_size(const Tuple *tuple) {
    if (tuple == NULL || tuple->data == NULL) {
        return 0;
    }
    return tuple->size;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    Tuple t = {arr, sizeof(arr) / sizeof(arr[0])};

    size_t size = get_size(&t);
    printf("Size of tuple: %zu\n", size);

    return 0;
}