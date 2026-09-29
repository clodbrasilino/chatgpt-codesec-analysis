#include <stdio.h>
#include <stdlib.h>

size_t count_before(const int *tuple, size_t tuple_size, int record) {
    if (tuple == NULL) {
        return 0;
    }

    for (size_t i = 0; i < tuple_size; i++) {
        if (tuple[i] == record) {
            return i;
        }
    }

    return tuple_size;
}

int main(void) {
    int data[] = {10, 20, 30, 40, 50, 30};
    size_t size = sizeof(data) / sizeof(data[0]);
    int target = 40;

    size_t result = count_before(data, size, target);

    printf("%zu\n", result);

    return 0;
}