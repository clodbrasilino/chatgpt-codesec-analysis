#include <stdio.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

void maximize(Tuple *x, Tuple *y) {
    if(!x || !y) {
        printf("Error: Null pointer provided.\n");
        return;
    }

    if(y->a > x->a) {
        x->a = y->a;
    }

    if(y->b > x->b) {
        x->b = y->b;
    }
}

int main() {
    Tuple x = {5, 10};
    Tuple y = {10, 5};

    maximize(&x, &y);

    printf("Maximized tuple: a=%d, b=%d\n", x.a, x.b);

    return 0;
}