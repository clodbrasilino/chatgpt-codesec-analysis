#include <stdio.h>

typedef struct {
    int initial;
    int last;
} Tuple;

void getInitialAndLast(Tuple* tuple, int* initial, int *last) {
    if (tuple == NULL || initial == NULL || last == NULL) {
        return;
    }
    *initial = tuple->initial;
    *last = tuple->last;
}

int main() {
    Tuple tuple = { .initial=10, .last=20 };
    int initial, last;

    getInitialAndLast(&tuple, &initial, &last);

    printf("Initial: %d\n", initial);
    printf("Last: %d\n", last);

    return 0;
}