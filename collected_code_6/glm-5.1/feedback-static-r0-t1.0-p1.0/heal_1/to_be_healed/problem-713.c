#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

bool is_valid_tuple(const Tuple *t) {
    if (t == NULL) {
        return false;
    }

    if (t->a == 0 || t->b == 0 || t->c == 0) {
        return false;
    }

    return true;
}

int main(void) {
    Tuple t1 = {1, 2, 3};
    Tuple t2 = {0, 5, 6};
    /* Possible weaknesses found:
     *  Variable 't3' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *t3 = NULL;

    printf("%d\n", is_valid_tuple(&t1));
    printf("%d\n", is_valid_tuple(&t2));
    printf("%d\n", is_valid_tuple(t3));

    return 0;
}