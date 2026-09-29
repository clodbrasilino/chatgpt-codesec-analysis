#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple *tuple_modulo(const Tuple *a, const Tuple *b) {
    if (a == NULL || b == NULL || a->data == NULL || b->data == NULL) {
        return NULL;
    }
    if (a->size != b->size || a->size <= 0) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->size = a->size;
    result->data = (int *)malloc(sizeof(int) * result->size);
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < result->size; i++) {
        if (b->data[i] == 0) {
            free(result->data);
            free(result);
            return NULL;
        }
        result->data[i] = a->data[i] % b->data[i];
    }

    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

void print_tuple(const Tuple *tuple) {
    if (tuple == NULL || tuple->data == NULL) {
        printf("NULL\n");
        return;
    }
    printf("(");
    for (int i = 0; i < tuple->size; i++) {
        printf("%d", tuple->data[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    int a_data[] = {10, 20, 30};
    int b_data[] = {3, 7, 4};
    int c_data[] = {5, 0, 2};

    Tuple a = {a_data, 3};
    Tuple b = {b_data, 3};
    Tuple c = {c_data, 3};

    Tuple *result = tuple_modulo(&a, &b);
    printf("Modulo of a and b: ");
    print_tuple(result);
    free_tuple(result);

    result = tuple_modulo(&a, &c);
    printf("Modulo of a and c: ");
    print_tuple(result);
    free_tuple(result);

    result = tuple_modulo(NULL, &b);
    printf("Modulo with NULL: ");
    print_tuple(result);
    free_tuple(result);

    return 0;
}