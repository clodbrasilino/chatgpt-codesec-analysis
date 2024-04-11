#include <stdio.h>

typedef struct {
    int initial;
    int last;
} Tuple;

void accessData(Tuple *tuple) {
    printf("Initial: %d\n", tuple->initial);
    printf("Last: %d\n", tuple->last);
}

int main() {
    Tuple tuple = {5, 10};
    accessData(&tuple);
    return 0;
}