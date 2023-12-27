#include <stdio.h>

void shiftLastToFirst(int *list, const int size) {
    if(size <= 0) { return; }
    int last = list[size - 1];
    for(int i = size - 1; i > 0; i--) {
        list[i] = list[i - 1];
    }
    list[0] = last;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);

    shiftLastToFirst(list, size);

    for(int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}