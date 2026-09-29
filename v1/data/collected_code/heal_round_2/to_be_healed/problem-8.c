#include <stdio.h>

void squareElements(const int* list, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  assignment of read-only location '*(list + (sizetype)((long unsigned int)i * 4))'
         */
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