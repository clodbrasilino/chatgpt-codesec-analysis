#include <stdio.h>

typedef struct {
    int isTuple;
    int value;
} Element;

int countElementsUntilTuple(Element* list, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].isTuple) {
            break;
        }
        count++;
    }
    return count;
}

int main() {
    Element list[5] = {
        {0, 1},
        {0, 2},
        {1, 3},
        {0, 4},
        {0, 5}
    };
    int count = countElementsUntilTuple(list, 5);
    printf("Count: %d\n", count);
    return 0;
}