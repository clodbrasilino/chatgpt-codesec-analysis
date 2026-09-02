#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

Tuple* create_tuple(int a, int b, int c) {
    Tuple* t = (Tuple*)malloc(sizeof(Tuple));
    t->a = a;
    t->b = b;
    t->c = c;
    return t;
}

/* Possible weaknesses found:
 *  expected 'const Tuple *' but argument is of type 'Tuple **'
 */
int is_all_none(const Tuple* t) {
    return t->a == 0 && t->b == 0 && t->c == 0;
}

void remove_all_none_tuples(Tuple** list, int* size) {
    int i, j;
    for (i = 0, j = 0; i < *size; i++) {
        /* Possible weaknesses found:
         *  passing argument 1 of 'is_all_none' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        if (!is_all_none(&list[i])) {
            list[j] = list[i];
            j++;
        } else {
            free(list[i]);
        }
    }
    *size = j;
}

int main() {
    int size = 5;
    Tuple* list[5] = {
        create_tuple(1, 2, 3),
        create_tuple(0, 0, 0),
        create_tuple(4, 5, 6),
        create_tuple(0, 0, 0),
        create_tuple(7, 8, 9)
    };

    remove_all_none_tuples(list, &size);

    for (int i = 0; i < size; i++) {
        printf("(%d, %d, %d)\n", list[i]->a, list[i]->b, list[i]->c);
        free(list[i]);
    }

    return 0;
}