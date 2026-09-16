#include <stdio.h>
#include <stdbool.h>

bool contains(const int *sequence, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (sequence[i] == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int sequence[] = {1, 2, 3, 4, 5};
    int size = 5;
    int value = 3;
    if (contains(sequence, size, value)) {
        printf("Value %d exists in the sequence.\n", value);
    } else {
        printf("Value %d does not exist in the sequence.\n", value);
    }
    return 0;
}