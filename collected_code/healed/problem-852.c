#include <stdio.h>

void removeNegative(int* list, const int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] >= 0) {
            list[count++] = list[i];
        }
    }
    while (count < size) {
        list[count++] = 0;
    }
}

int main() {
    int list[] = {1, -2, 3, -4, 5, -6};
    const int size = sizeof(list) / sizeof(list[0]);

    removeNegative(list, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    return 0;
}