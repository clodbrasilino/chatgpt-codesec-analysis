#include <stdio.h>

typedef struct {
    int first;
    int second;
    int third;
} Tuple;

int getTupleItem(Tuple tuple, int index) {
    switch(index) {
        case 0:
            return tuple.first;
        case 1:
            return tuple.second;
        case 2:
            return tuple.third;
        default:
            printf("Invalid index\n");
            return -1;
    }
}

int main() {
    Tuple tuple;
    tuple.first = 1;
    tuple.second = 2;
    tuple.third = 3;

    printf("First item: %d\n", getTupleItem(tuple, 0));
    printf("Second item: %d\n", getTupleItem(tuple, 1));
    printf("Third item: %d\n", getTupleItem(tuple, 2));

    return 0;
}