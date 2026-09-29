#include <stdio.h>

typedef struct {
    int id;
    int value;
} Tuple;

int findMax(Tuple* list, int size) {
    int max = list[0].value;
    for(int i = 1; i < size; i++) {
        if(list[i].value > max) {
            max = list[i].value;
        }
    }
    return max;
}

int main() {
    Tuple list[] = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    int size = sizeof(list) / sizeof(Tuple);
    int max = findMax(list, size);
    printf("The maximum value is %d\n", max);
    return 0;
}