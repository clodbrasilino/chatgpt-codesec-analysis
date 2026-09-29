#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

bool tuple_contains(const Tuple *tuple, int k)
{
    if (tuple == NULL || tuple->data == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->data[i] == k) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5};
    Tuple tuple = {values, sizeof(values) / sizeof(values[0])};
    int k = 3;

    if (tuple_contains(&tuple, k)) {
        printf("Tuple contains %d\n", k);
    } else {
        printf("Tuple does not contain %d\n", k);
    }

    return 0;
}