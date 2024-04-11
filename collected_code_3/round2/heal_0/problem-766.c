#include <stdio.h>

void iterate_pairs(int* list, int size) {
    for(int i = 0; i < size - 1; i++) {
        printf("Pair: %d, %d\n", list[i], list[i+1]);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(list)/sizeof(list[0]);

    iterate_pairs(list, size);

    return 0;
}