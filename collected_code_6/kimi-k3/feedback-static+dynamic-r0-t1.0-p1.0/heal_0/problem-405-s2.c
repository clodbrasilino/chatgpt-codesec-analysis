#include <stdio.h>
#include <stddef.h>

typedef struct {
    int x;
    int y;
    int z;
} Tuple3;

int tuple_contains(const Tuple3 *t, int element) {
    if (t == NULL) {
        return 0;
    }
    return (t->x == element || t->y == element || t->z == element);
}

int main(void) {
    Tuple3 t = {10, 20, 30};
    int element = 20;

    if (tuple_contains(&t, element)) {
        printf("Element %d exists in the tuple\n", element);
    } else {
        printf("Element %d does not exist in the tuple\n", element);
    }

    return 0;
}