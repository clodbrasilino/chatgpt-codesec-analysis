#include <stdio.h>

typedef struct Tuple {
    int *items;
    int size;
} Tuple;

int findSize(Tuple *tuple) {
    if(tuple == NULL) {
        printf("Error: NULL pointer passed. \n");
        return -1;
    }
    return tuple->size;
}

int main(void) {
    Tuple tuple;
    int items[3] = {1, 2, 3};

    tuple.items = items;
    tuple.size = sizeof(items)/sizeof(int);

    int size = findSize(&tuple);
    if (size != -1) {
        printf("Size of the tuple is: %d\n", size);
    }

    return 0;
}