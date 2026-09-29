#include <stdio.h>

void iterate_pairs(int* list, int size) {
    if(list == NULL || size <= 0) {
        printf("Invalid parameters\n");
        return;
    }

    for(int i = 0; i < size - 1; i++) {
        printf("(%d, %d)\n", list[i], list[i + 1]);
    }
}

int main() {
    int size = 5;
    int list[] = {1, 2, 3, 4, 5};

    iterate_pairs(list, size);

    return 0;
}