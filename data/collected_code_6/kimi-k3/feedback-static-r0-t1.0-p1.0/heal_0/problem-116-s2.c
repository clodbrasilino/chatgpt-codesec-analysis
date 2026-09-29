#include <stdio.h>
#include <limits.h>

typedef struct {
    unsigned int *data;
    size_t size;
} Tuple;

int tuple_to_int(const Tuple *tuple, int *result) {
    if (tuple == NULL || result == NULL || tuple->size == 0 || tuple->data == NULL) {
        return -1;
    }

    int value = 0;
    size_t i;
    for (i = 0; i < tuple->size; i++) {
        if (tuple->data[i] > 9) {
            return -1;
        }
        if (value > (INT_MAX - (int)tuple->data[i]) / 10) {
            return -1;
        }
        value = value * 10 + (int)tuple->data[i];
    }

    *result = value;
    return 0;
}

int main(void) {
    unsigned int data[] = {1, 2, 3, 4, 5};
    Tuple tuple;
    int result;

    tuple.data = data;
    tuple.size = sizeof(data) / sizeof(data[0]);

    if (tuple_to_int(&tuple, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Conversion failed\n");
    }

    return 0;
}