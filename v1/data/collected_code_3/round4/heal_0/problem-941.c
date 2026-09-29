#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

int countUntilTuple(Tuple* list, int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(list[i].first != 0 && list[i].second != 0) {
            break;
        }
        count++;
    }
    return count;
}

int main() {
    Tuple list[10] = {
        {0, 0},
        {0, 0},
        {0, 0},
        {1, 2},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };

    int count = countUntilTuple(list, 10);
    printf("Count until tuple: %d\n", count);

    return 0;
}