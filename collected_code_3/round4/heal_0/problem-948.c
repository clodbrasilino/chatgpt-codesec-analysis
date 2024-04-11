#include <stdio.h>

typedef struct {
    int item1;
    int item2;
    int item3;
} Tuple;

int getTupleItem(Tuple* tuple, int itemIndex) {
    switch(itemIndex) {
        case 1:
            return tuple->item1;
        case 2:
            return tuple->item2;
        case 3:
            return tuple->item3;
        default:
            printf("Invalid item index.\n");
            return -1;
    }
}

int main() {
    Tuple tuple = {10, 20, 30};
    int item = getTupleItem(&tuple, 2);
    printf("Item: %d\n", item);
    return 0;
}