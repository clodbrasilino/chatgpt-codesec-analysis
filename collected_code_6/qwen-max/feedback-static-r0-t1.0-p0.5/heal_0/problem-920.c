#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

Tuple* create_tuple(int a, int b, int c) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    t->a = a;
    t->b = b;
    t->c = c;
    return t;
}

void free_tuple_list(Tuple **list, int size) {
    for (int i = 0; i < size; ++i) {
        if (list[i] != NULL) {
            free(list[i]);
        }
    }
    free(list);
}

int remove_none_tuples(Tuple **list, int *size) {
    int write_index = 0;
    for (int i = 0; i < *size; ++i) {
        if (list[i]->a != -1 || list[i]->b != -1 || list[i]->c != -1) {
            list[write_index++] = list[i];
        } else {
            free(list[i]);
        }
    }
    *size = write_index;
    return 0;
}

int main() {
    int initial_size = 5;
    Tuple **tuple_list = (Tuple **)malloc(initial_size * sizeof(Tuple *));
    tuple_list[0] = create_tuple(1, 2, 3);
    tuple_list[1] = create_tuple(-1, -1, -1);
    tuple_list[2] = create_tuple(4, 5, 6);
    tuple_list[3] = create_tuple(-1, -1, -1);
    tuple_list[4] = create_tuple(7, 8, 9);

    int size = initial_size;
    remove_none_tuples(tuple_list, &size);

    for (int i = 0; i < size; ++i) {
        printf("(%d, %d, %d)\n", tuple_list[i]->a, tuple_list[i]->b, tuple_list[i]->c);
    }

    free_tuple_list(tuple_list, initial_size);
    return 0;
}