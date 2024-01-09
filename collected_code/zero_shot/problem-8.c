#include <stdio.h>

void squareElements(int* list, int size) {
    for (int i = 0; i < size; i++) {
        list[i] = list[i] * list[i];
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);

    squareElements(list, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    return 0;
}