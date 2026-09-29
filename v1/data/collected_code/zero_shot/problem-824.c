#include <stdio.h>

void removeEvenNumbers(int *list, int size) {
    int i, j;
    j = 0;
    for (i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            list[j] = list[i];
            j++;
        }
    }
    for (i = j; i < size; i++) {
        list[i] = 0;
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);

    removeEvenNumbers(list, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    return 0;
}